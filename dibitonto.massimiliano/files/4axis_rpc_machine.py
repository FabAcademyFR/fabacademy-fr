# Two stage example Virtual Machine file
# moves get set in Main
# usb port needs to be set in initInterfaces
# Nadya Peek Dec 2014

#------IMPORTS-------
from pygestalt import nodes
from pygestalt import interfaces
from pygestalt import machines
from pygestalt import functions
from pygestalt.machines import elements
from pygestalt.machines import kinematics
from pygestalt.machines import state
from pygestalt.utilities import notice
from pygestalt.publish import rpc	#remote procedure call dispatcher
import time
import io


#------VIRTUAL MACHINE------
class virtualMachine(machines.virtualMachine):
	
	def initInterfaces(self):
		if self.providedInterface: self.fabnet = self.providedInterface		#providedInterface is defined in the virtualMachine class.
		else: self.fabnet = interfaces.gestaltInterface('FABNET', interfaces.serialInterface(baudRate = 115200, interfaceType = 'ftdi', portName = '/dev/tty.usbserial-FTXW9L60'))
		
	def initControllers(self):
		self.xAxisNode = nodes.networkedGestaltNode('X Axis', self.fabnet, filename = '086-005a.py', persistence = self.persistence)
		self.yAxisNode = nodes.networkedGestaltNode('Y Axis', self.fabnet, filename = '086-005a.py', persistence = self.persistence)
		self.zAxisNode = nodes.networkedGestaltNode('Z Axis', self.fabnet, filename = '086-005a.py', persistence = self.persistence)
		self.kAxisNode = nodes.networkedGestaltNode('K Axis', self.fabnet, filename = '086-005a.py', persistence = self.persistence)
		#self.zkNode = nodes.compoundNode(self.yAxisNode, self.kAxisNode)
		self.xyzkNode = nodes.compoundNode(self.xAxisNode, self.yAxisNode, self.zAxisNode,self.kAxisNode)
		#self.testNode = nodes.compoundNode(self.xAxisNode, self.yAxisNode, self.zkNode)


	def initCoordinates(self):
		self.position = state.coordinate(['mm','mm','mm','mm'])	#X,Y,Z,K
	
	def initKinematics(self):
		self.xAxis = elements.elementChain.forward([elements.microstep.forward(4), elements.stepper.forward(1.8), elements.pulley.forward(2), elements.invert.forward(False)])
		self.yAxis = elements.elementChain.forward([elements.microstep.forward(4), elements.stepper.forward(1.8), elements.pulley.forward(2), elements.invert.forward(False)])
		self.zAxis = elements.elementChain.forward([elements.microstep.forward(4), elements.stepper.forward(1.8), elements.pulley.forward(2), elements.invert.forward(False)])
		self.kAxis = elements.elementChain.forward([elements.microstep.forward(4), elements.stepper.forward(1.8), elements.pulley.forward(2), elements.invert.forward(False)])

		self.stageKinematics = kinematics.direct(4)	#direct drive on all four axes
	
	def initFunctions(self):
		self.move = functions.move(virtualMachine = self, virtualNode = self.xyzkNode, axes = [self.xAxis, self.yAxis, self.zAxis, self.kAxis], kinematics = self.stageKinematics, machinePosition = self.position,
								planner = 'null')
		self.jog = functions.jog(self.move)	#an incremental wrapper for the move function
		pass
		
	def initLast(self):
#		self.machineControl.setMotorCurrents(aCurrent = 0.8, bCurrent = 0.8, cCurrent = 0.8)
#		self.xyzkNode.setVelocityRequest(0)	#clear velocity on nodes. Eventually this will be put in the motion planner on initialization to match state.
		pass
	
	def publish(self):
		#self.publisher.addNodes(self.machineControl)
		pass
	
	def getPosition(self):
		return {'position':self.position.future()}
	
	def setPosition(self, position  = [None, None, None, None]):
		self.position.future.set(position)

	def setSpindleSpeed(self, speedFraction):
		#self.machineControl.pwmRequest(speedFraction)
		pass
	
		

#------IF RUN DIRECTLY FROM TERMINAL------
if __name__ == '__main__':
	desktopFactory = virtualMachine(persistenceFile = "test.vmp")
#	desktopFactory.xyzNode.setMotorCurrent(1.1)
	#desktopFactory.xyzNode.loadProgram('../../../086-005/086-005a.hex')
	desktopFactory.xyzkNode.setVelocityRequest(8)
	#desktopFactory.xyzNode.setMotorCurrent(1)
	#desktopFactory.setPosition([0,0,0,0]);
	fileReader = rpc.fileRPCDispatch()
	fileReader.addFunctions(('move',desktopFactory.move), ('jog', desktopFactory.jog))	#expose these functions on the file reader interface.
	#desktopFactory.move([None,0,10,10],0)
	#desktopFactory.move([-10,0,-10,-10],0)
	#desktopFactory.move([30,10,30,30],0)
	#desktopFactory.move([20,0,50,50],0)
	#desktopFactory.move([150,150,None,None],0)
	time.sleep(1)


	rpcDispatch = rpc.httpRPCDispatch(address = '0.0.0.0', port = 27272)
	notice(desktopFactory, 'Started remote procedure call dispatcher on ' + str(rpcDispatch.address) + ', port ' + str(rpcDispatch.port))
	rpcDispatch.addFunctions(('move',desktopFactory.move),
				('position', desktopFactory.getPosition),
				('jog', desktopFactory.jog),
				('disableMotors', desktopFactory.xyzkNode.disableMotorsRequest),
				('loadRemote', fileReader.loadFromURL),
				('loadLocal', fileReader.loadFromFile),
				('runFile', fileReader.runFile),
				('setPosition', desktopFactory.setPosition))	#expose these functions on an http interface
	rpcDispatch.addOrigins('http://tq.mit.edu', 'http://127.0.0.1')	#allow scripts from these sites to access the RPC interface
	rpcDispatch.allowAllOrigins()
	rpcDispatch.start()

 
	


