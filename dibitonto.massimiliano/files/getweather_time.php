<?php

$result = file_get_contents('http://weather.yahooapis.com/forecastrss?w=721943&u=c');
$xml = simplexml_load_string($result);

//echo htmlspecialchars($result, ENT_QUOTES, 'UTF-8');

$xml->registerXPathNamespace('yweather', 'http://xml.weather.yahoo.com/ns/rss/1.0');
$location = $xml->channel->xpath('yweather:location');
$astr =  $xml->channel->xpath('yweather:astronomy');
echo("/123/");


if(!empty($location)){
    foreach($xml->channel->item as $item){
        $current = $item->xpath('yweather:condition');
        $forecast = $item->xpath('yweather:forecast');
        $current = $current[0];
       // $output = <<<END
            echo $current['temp']."/"; //current temp
            echo $forecast[0]['code']."/"; //current forecast code
            echo $forecast[0]['high']."/"; //max temp expected today
            echo $forecast[0]['low']."/";//min temp expected today
            echo $forecast[0]['code']."/";//forecast code for tomorrow

$sunr = $astr[0]['sunrise']; //several operation to transform h:min pm into h:min
$sunr = trim($sunr);
$sunr = explode(":",$sunr);
$sunr_h=$sunr[0];
$sunr_m_a = explode(" ",$sunr[1]);
$sunr_m = $sunr_m_a[0];
//echo $sunr_h."/";
//echo $sunr_m."/";

$suns = $astr[0]['sunset']; //several operation to transform h:min pm into h:min
$suns = trim($suns);
$suns = explode(":",$suns);
$suns_h=$suns[0];
$suns_m_a = explode(" ",$suns[1]);
$suns_m = $suns_m_a[0];
//echo $suns_h."/";
//echo $suns_m."/";
    }
}else{
    $output = '<h1>99</h1>';
    echo $output;
}

 
$hour = date('G', time()); //24h format without 0
echo $hour."/";
$min = 1*(date('i'));
echo $min."/";
$weekday = date('w');
echo $weekday;
?>
