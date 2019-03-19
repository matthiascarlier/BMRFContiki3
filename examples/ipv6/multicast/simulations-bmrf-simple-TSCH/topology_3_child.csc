<?xml version="1.0" encoding="UTF-8"?>
<simconf>
  <project EXPORT="discard">[APPS_DIR]/mrm</project>
  <project EXPORT="discard">[APPS_DIR]/mspsim</project>
  <project EXPORT="discard">[APPS_DIR]/avrora</project>
  <project EXPORT="discard">[APPS_DIR]/serial_socket</project>
  <project EXPORT="discard">[APPS_DIR]/collect-view</project>
  <project EXPORT="discard">[APPS_DIR]/powertracker</project>
  <simulation>
    <title>BMRF-test-sky</title>
    <randomseed>#randomseed#</randomseed>
    <motedelay_us>1000000</motedelay_us>
    <radiomedium>
      org.contikios.cooja.radiomediums.UDGM
      <transmitting_range>50.0</transmitting_range>
      <interference_range>50.0</interference_range>
      <success_ratio_tx>1.0</success_ratio_tx>
      <success_ratio_rx>1.0</success_ratio_rx>
    </radiomedium>
    <events>
      <logoutput>40000</logoutput>
    </events>
    <motetype>
      org.contikios.cooja.mspmote.SkyMoteType
      <identifier>sky1</identifier>
      <description>root</description>
      <source EXPORT="discard">[CONTIKI_DIR]/examples/ipv6/multicast/simulations-bmrf/root.c</source>
      <commands EXPORT="discard">make root.sky TARGET=sky</commands>
      <firmware EXPORT="copy">[CONTIKI_DIR]/examples/ipv6/multicast/simulations-bmrf/root.sky</firmware>
      <moteinterface>org.contikios.cooja.interfaces.Position</moteinterface>
      <moteinterface>org.contikios.cooja.interfaces.RimeAddress</moteinterface>
      <moteinterface>org.contikios.cooja.interfaces.IPAddress</moteinterface>
      <moteinterface>org.contikios.cooja.interfaces.Mote2MoteRelations</moteinterface>
      <moteinterface>org.contikios.cooja.interfaces.MoteAttributes</moteinterface>
      <moteinterface>org.contikios.cooja.mspmote.interfaces.MspClock</moteinterface>
      <moteinterface>org.contikios.cooja.mspmote.interfaces.MspMoteID</moteinterface>
      <moteinterface>org.contikios.cooja.mspmote.interfaces.SkyButton</moteinterface>
      <moteinterface>org.contikios.cooja.mspmote.interfaces.SkyFlash</moteinterface>
      <moteinterface>org.contikios.cooja.mspmote.interfaces.SkyCoffeeFilesystem</moteinterface>
      <moteinterface>org.contikios.cooja.mspmote.interfaces.Msp802154Radio</moteinterface>
      <moteinterface>org.contikios.cooja.mspmote.interfaces.MspSerial</moteinterface>
      <moteinterface>org.contikios.cooja.mspmote.interfaces.SkyLED</moteinterface>
      <moteinterface>org.contikios.cooja.mspmote.interfaces.MspDebugOutput</moteinterface>
      <moteinterface>org.contikios.cooja.mspmote.interfaces.SkyTemperature</moteinterface>
    </motetype>
    <motetype>
      org.contikios.cooja.mspmote.SkyMoteType
      <identifier>sky2</identifier>
      <description>intermediate</description>
      <source EXPORT="discard">[CONTIKI_DIR]/examples/ipv6/multicast/simulations-bmrf/intermediate.c</source>
      <commands EXPORT="discard">make intermediate.sky TARGET=sky</commands>
      <firmware EXPORT="copy">[CONTIKI_DIR]/examples/ipv6/multicast/simulations-bmrf/intermediate.sky</firmware>
      <moteinterface>org.contikios.cooja.interfaces.Position</moteinterface>
      <moteinterface>org.contikios.cooja.interfaces.RimeAddress</moteinterface>
      <moteinterface>org.contikios.cooja.interfaces.IPAddress</moteinterface>
      <moteinterface>org.contikios.cooja.interfaces.Mote2MoteRelations</moteinterface>
      <moteinterface>org.contikios.cooja.interfaces.MoteAttributes</moteinterface>
      <moteinterface>org.contikios.cooja.mspmote.interfaces.MspClock</moteinterface>
      <moteinterface>org.contikios.cooja.mspmote.interfaces.MspMoteID</moteinterface>
      <moteinterface>org.contikios.cooja.mspmote.interfaces.SkyButton</moteinterface>
      <moteinterface>org.contikios.cooja.mspmote.interfaces.SkyFlash</moteinterface>
      <moteinterface>org.contikios.cooja.mspmote.interfaces.SkyCoffeeFilesystem</moteinterface>
      <moteinterface>org.contikios.cooja.mspmote.interfaces.Msp802154Radio</moteinterface>
      <moteinterface>org.contikios.cooja.mspmote.interfaces.MspSerial</moteinterface>
      <moteinterface>org.contikios.cooja.mspmote.interfaces.SkyLED</moteinterface>
      <moteinterface>org.contikios.cooja.mspmote.interfaces.MspDebugOutput</moteinterface>
      <moteinterface>org.contikios.cooja.mspmote.interfaces.SkyTemperature</moteinterface>
    </motetype>
    <motetype>
      org.contikios.cooja.mspmote.SkyMoteType
      <identifier>sky3</identifier>
      <description>sink</description>
      <source EXPORT="discard">[CONTIKI_DIR]/examples/ipv6/multicast/simulations-bmrf/sink.c</source>
      <commands EXPORT="discard">make sink.sky TARGET=sky</commands>
      <firmware EXPORT="copy">[CONTIKI_DIR]/examples/ipv6/multicast/simulations-bmrf/sink.sky</firmware>
      <moteinterface>org.contikios.cooja.interfaces.Position</moteinterface>
      <moteinterface>org.contikios.cooja.interfaces.RimeAddress</moteinterface>
      <moteinterface>org.contikios.cooja.interfaces.IPAddress</moteinterface>
      <moteinterface>org.contikios.cooja.interfaces.Mote2MoteRelations</moteinterface>
      <moteinterface>org.contikios.cooja.interfaces.MoteAttributes</moteinterface>
      <moteinterface>org.contikios.cooja.mspmote.interfaces.MspClock</moteinterface>
      <moteinterface>org.contikios.cooja.mspmote.interfaces.MspMoteID</moteinterface>
      <moteinterface>org.contikios.cooja.mspmote.interfaces.SkyButton</moteinterface>
      <moteinterface>org.contikios.cooja.mspmote.interfaces.SkyFlash</moteinterface>
      <moteinterface>org.contikios.cooja.mspmote.interfaces.SkyCoffeeFilesystem</moteinterface>
      <moteinterface>org.contikios.cooja.mspmote.interfaces.Msp802154Radio</moteinterface>
      <moteinterface>org.contikios.cooja.mspmote.interfaces.MspSerial</moteinterface>
      <moteinterface>org.contikios.cooja.mspmote.interfaces.SkyLED</moteinterface>
      <moteinterface>org.contikios.cooja.mspmote.interfaces.MspDebugOutput</moteinterface>
      <moteinterface>org.contikios.cooja.mspmote.interfaces.SkyTemperature</moteinterface>
    </motetype>
    <mote>
      <breakpoints />
      <interface_config>
        org.contikios.cooja.interfaces.Position
        <x>99.24558214386008</x>
        <y>-96.98108515463512</y>
        <z>0.0</z>
      </interface_config>
      <interface_config>
        org.contikios.cooja.mspmote.interfaces.MspMoteID
        <id>1</id>
      </interface_config>
      <motetype_identifier>sky1</motetype_identifier>
    </mote>
    <mote>
      <breakpoints />
      <interface_config>
        org.contikios.cooja.interfaces.Position
        <x>55.413630253220255</x>
        <y>-97.81199003026448</y>
        <z>0.0</z>
      </interface_config>
      <interface_config>
        org.contikios.cooja.mspmote.interfaces.MspMoteID
        <id>2</id>
      </interface_config>
      <motetype_identifier>sky3</motetype_identifier>
    </mote>
    <mote>
      <breakpoints />
      <interface_config>
        org.contikios.cooja.interfaces.Position
        <x>116.49863938742673</x>
        <y>-129.0852916357065</y>
        <z>0.0</z>
      </interface_config>
      <interface_config>
        org.contikios.cooja.mspmote.interfaces.MspMoteID
        <id>3</id>
      </interface_config>
      <motetype_identifier>sky3</motetype_identifier>
    </mote>
    <mote>
      <breakpoints />
      <interface_config>
        org.contikios.cooja.interfaces.Position
        <x>117.93185478817963</x>
        <y>-62.613625992843325</y>
        <z>0.0</z>
      </interface_config>
      <interface_config>
        org.contikios.cooja.mspmote.interfaces.MspMoteID
        <id>4</id>
      </interface_config>
      <motetype_identifier>sky3</motetype_identifier>
    </mote>
    <mote>
      <breakpoints />
      <interface_config>
        org.contikios.cooja.interfaces.Position
        <x>25.5535051488539</x>
        <y>-63.26063739291746</y>
        <z>0.0</z>
      </interface_config>
      <interface_config>
        org.contikios.cooja.mspmote.interfaces.MspMoteID
        <id>5</id>
      </interface_config>
      <motetype_identifier>sky3</motetype_identifier>
    </mote>
    <mote>
      <breakpoints />
      <interface_config>
        org.contikios.cooja.interfaces.Position
        <x>11.39815445192653</x>
        <y>-114.48401885667977</y>
        <z>0.0</z>
      </interface_config>
      <interface_config>
        org.contikios.cooja.mspmote.interfaces.MspMoteID
        <id>6</id>
      </interface_config>
      <motetype_identifier>sky3</motetype_identifier>
    </mote>
    <mote>
      <breakpoints />
      <interface_config>
        org.contikios.cooja.interfaces.Position
        <x>56.825814313976025</x>
        <y>-140.3904535054232</y>
        <z>0.0</z>
      </interface_config>
      <interface_config>
        org.contikios.cooja.mspmote.interfaces.MspMoteID
        <id>7</id>
      </interface_config>
      <motetype_identifier>sky3</motetype_identifier>
    </mote>
    <mote>
      <breakpoints />
      <interface_config>
        org.contikios.cooja.interfaces.Position
        <x>105.24758496042645</x>
        <y>-170.3214890168393</y>
        <z>0.0</z>
      </interface_config>
      <interface_config>
        org.contikios.cooja.mspmote.interfaces.MspMoteID
        <id>8</id>
      </interface_config>
      <motetype_identifier>sky3</motetype_identifier>
    </mote>
    <mote>
      <breakpoints />
      <interface_config>
        org.contikios.cooja.interfaces.Position
        <x>155.7816335663373</x>
        <y>-154.87673730322922</y>
        <z>0.0</z>
      </interface_config>
      <interface_config>
        org.contikios.cooja.mspmote.interfaces.MspMoteID
        <id>9</id>
      </interface_config>
      <motetype_identifier>sky3</motetype_identifier>
    </mote>
    <mote>
      <breakpoints />
      <interface_config>
        org.contikios.cooja.interfaces.Position
        <x>153.44796639040595</x>
        <y>-101.31990843823355</y>
        <z>0.0</z>
      </interface_config>
      <interface_config>
        org.contikios.cooja.mspmote.interfaces.MspMoteID
        <id>10</id>
      </interface_config>
      <motetype_identifier>sky3</motetype_identifier>
    </mote>
    <mote>
      <breakpoints />
      <interface_config>
        org.contikios.cooja.interfaces.Position
        <x>160.87806425421383</x>
        <y>-51.03561110331621</y>
        <z>0.0</z>
      </interface_config>
      <interface_config>
        org.contikios.cooja.mspmote.interfaces.MspMoteID
        <id>11</id>
      </interface_config>
      <motetype_identifier>sky3</motetype_identifier>
    </mote>
    <mote>
      <breakpoints />
      <interface_config>
        org.contikios.cooja.interfaces.Position
        <x>118.50950689501134</x>
        <y>-18.057969419616015</y>
        <z>0.0</z>
      </interface_config>
      <interface_config>
        org.contikios.cooja.mspmote.interfaces.MspMoteID
        <id>12</id>
      </interface_config>
      <motetype_identifier>sky3</motetype_identifier>
    </mote>
    <mote>
      <breakpoints />
      <interface_config>
        org.contikios.cooja.interfaces.Position
        <x>76.92316920454059</x>
        <y>-49.44284637240423</y>
        <z>0.0</z>
      </interface_config>
      <interface_config>
        org.contikios.cooja.mspmote.interfaces.MspMoteID
        <id>13</id>
      </interface_config>
      <motetype_identifier>sky3</motetype_identifier>
    </mote>
  </simulation>
  <plugin>
    org.contikios.cooja.plugins.SimControl
    <width>280</width>
    <z>1</z>
    <height>160</height>
    <location_x>34</location_x>
    <location_y>522</location_y>
  </plugin>
  <plugin>
    org.contikios.cooja.plugins.Visualizer
    <plugin_config>
      <moterelations>true</moterelations>
      <skin>org.contikios.cooja.plugins.skins.IDVisualizerSkin</skin>
      <skin>org.contikios.cooja.plugins.skins.GridVisualizerSkin</skin>
      <skin>org.contikios.cooja.plugins.skins.TrafficVisualizerSkin</skin>
      <skin>org.contikios.cooja.plugins.skins.UDGMVisualizerSkin</skin>
      <skin>org.contikios.cooja.plugins.skins.MoteTypeVisualizerSkin</skin>
      <viewport>2.6449360542340754 0.0 0.0 2.6449360542340754 56.17020892850724 470.1258107478351</viewport>
    </plugin_config>
    <width>578</width>
    <z>0</z>
    <height>496</height>
    <location_x>845</location_x>
    <location_y>70</location_y>
  </plugin>
  <plugin>
    org.contikios.cooja.plugins.LogListener
    <plugin_config>
      <filter>ID:13</filter>
      <formatted_time />
      <coloring />
    </plugin_config>
    <width>687</width>
    <z>2</z>
    <height>822</height>
    <location_x>646</location_x>
    <location_y>-15</location_y>
  </plugin>
  <plugin>
    PowerTracker
    <width>579</width>
    <z>4</z>
    <height>523</height>
    <location_x>48</location_x>
    <location_y>41</location_y>
  </plugin>
  <plugin>
    org.contikios.cooja.plugins.ScriptRunner
    <plugin_config>
      <script>//import Java Package to JavaScript&#xD;
importPackage(java.io);&#xD;
&#xD;
simulation_time = 785000;&#xD;
&#xD;
TIMEOUT(900000, timeout_func()); /* milliseconds */&#xD;
&#xD;
outs = new Array(100);&#xD;
total_time = 0;&#xD;
total_ins = 0;&#xD;
&#xD;
pdr = 0;&#xD;
frame_tx = 0;&#xD;
msg_tx = 0;&#xD;
rx_time = 0;&#xD;
tx_time = 0;&#xD;
lpm_time = 0;&#xD;
cpu_time = 0;&#xD;
total_subscribed = 0;&#xD;
total_nodes = 0;&#xD;
&#xD;
fr = new File("raw_results.csv");&#xD;
fd = new File("delay_results.csv");&#xD;
fs = new File("summary_results.csv");&#xD;
fdup = new File("duplicates_results.csv");&#xD;
frawdup = new File("duplicates_raw_results.csv");&#xD;
//Use this if using the GUI &#xD;
//f = new File("../../../examples/ipv6/multicast/simulations-bmrf/log.txt");&#xD;
tfraw = new FileWriter(fr);&#xD;
tfdelay = new FileWriter(fd);&#xD;
tfsummary = new FileWriter(fs);&#xD;
tfduplicates = new FileWriter(fdup);&#xD;
tfraw_duplicates = new FileWriter(frawdup);&#xD;
&#xD;
timeout_func = function simulationEnd() {&#xD;
  /* Extract PowerTracker statistics */&#xD;
  plugin = mote.getSimulation().getCooja().getStartedPlugin("PowerTracker");&#xD;
  if (plugin != null) {&#xD;
    stats = plugin.radioStatistics();&#xD;
    splited_stats = stats.split(/\r\n|\n|\r/);&#xD;
    splited_on = splited_stats[0].split(" ");&#xD;
    splited_tx = splited_stats[1].split(" ");&#xD;
    splited_rx = splited_stats[2].split(" ");&#xD;
    splited_int = splited_stats[3].split(" ");&#xD;
    idle_listening = (splited_on[2]-splited_tx[2]-splited_rx[2])/(1000000*51);&#xD;
    //log.log("PowerTracker: Extracted statistics:\n"&#xD;
    //  + "AVG ON " + splited_on[2]/(1000000*51) + "s " + splited_on[4] + "%" +"\n"&#xD;
    //  + "AVG TX " + splited_tx[2]/(1000000*51) + "s " + splited_tx[4] + "%" + "\n"&#xD;
    //  + "AVG RX " + splited_rx[2]/(1000000*51) + "s " + splited_rx[4] + "%" + "\n"&#xD;
    //  + "AVG IDLE LISTENING " + idle_listening + "s " + idle_listening*100/(simulation_time/1000) + "%" + "\n"&#xD;
    //  + "AVG INT " + splited_int[2]/(1000000*51) + "s " + splited_int[4] + "%" + "\n"&#xD;
    //  + "\n");&#xD;
    tfsummary.write("PowerTracker: Extracted statistics:\n"&#xD;
    + "AVG ON " + splited_on[2]/(1000000*51) + "s " + splited_on[4] + "%" +"\n"&#xD;
    + "AVG TX " + splited_tx[2]/(1000000*51) + "s " + splited_tx[4] + "%" + "\n"&#xD;
    + "AVG RX " + splited_rx[2]/(1000000*51) + "s " + splited_rx[4] + "%" + "\n"&#xD;
    + "AVG IDLE LISTENING " + idle_listening + "s " + idle_listening*100/(simulation_time/1000) + "%" + "\n"&#xD;
    + "AVG INT " + splited_int[2]/(1000000*51) + "s " + splited_int[4] + "%" + "\n"&#xD;
    + "\n");&#xD;
  } else {&#xD;
    //log.log("No PowerTracker plugin\n");&#xD;
    tfsummary.write("No PowerTracker plugin\n");&#xD;
  }&#xD;
  //log.log("Average end-to-end delay: " + (total_time/total_ins) +"\n");&#xD;
  //log.log("Packet delivery ratio: " + (pdr/total_subscribed) + "\n");&#xD;
  //log.log("Frame transmission: " + (frame_tx/total_nodes) + "\n");&#xD;
  //log.log("Packet transmission: " + (msg_tx/total_nodes) + "\n");&#xD;
  //log.log("Rx time: " + (rx_time/total_nodes) + " = " + ((rx_time/total_nodes)/32768) + " s" + "\n");&#xD;
  //log.log("Tx time: " + (tx_time/total_nodes) + " = " + ((tx_time/total_nodes)/32768) + " s" + "\n");&#xD;
  //log.log("LPM time: " + (lpm_time/total_nodes) + " = " + ((lpm_time/total_nodes)/32768) + " s" + "\n");&#xD;
  //log.log("CPU time: " + (cpu_time/total_nodes) + " = " + ((cpu_time/total_nodes)/32768) + " s" + "\n");&#xD;
&#xD;
  tfsummary.write("Average end-to-end delay: " + (total_time/total_ins) +"\n");&#xD;
  tfsummary.write("Packet delivery ratio: " + (pdr/total_subscribed) + "\n");&#xD;
  tfsummary.write("Frame transmission: " + (frame_tx/total_nodes) + "\n");&#xD;
  tfsummary.write("Packet transmission: " + (msg_tx/total_nodes) + "\n");&#xD;
  tfsummary.write("Rx time: " + (rx_time/total_nodes) + " = " + ((rx_time/total_nodes)/32768) + " s" + "\n");&#xD;
  tfsummary.write("Tx time: " + (tx_time/total_nodes) + " = " + ((tx_time/total_nodes)/32768) + " s" + "\n");&#xD;
  tfsummary.write("LPM time: " + (lpm_time/total_nodes) + " = " + ((lpm_time/total_nodes)/32768) + " s" + "\n");&#xD;
  tfsummary.write("CPU time: " + (cpu_time/total_nodes) + " = " + ((cpu_time/total_nodes)/32768) + " s" + "\n");&#xD;
    &#xD;
  tfraw.close();&#xD;
  tfdelay.close();&#xD;
  tfsummary.close();&#xD;
  tfduplicates.close();&#xD;
  tfraw_duplicates.close();&#xD;
  log.testOK();&#xD;
}&#xD;
&#xD;
while(true){&#xD;
  YIELD();&#xD;
  time_msg = sim.getSimulationTimeMillis();&#xD;
  time_msg_seconds = time_msg/1000;&#xD;
  message = msg.split(";");&#xD;
  //log.log(""+message[0]+"\n");&#xD;
  if (message.length == 3) {&#xD;
    if (message[0]=="Out") {&#xD;
      outs[parseInt(message[1])] = time_msg;&#xD;
      //log.log("New out time\n");&#xD;
      //log.log("outs["+parseInt(message[1])+"] = "+outs[parseInt(message[1])]+" = "+time_msg+"\n");&#xD;
    } else if (message[0]=="In") {&#xD;
      total_time = total_time + (time_msg - outs[parseInt(message[1])]);&#xD;
      total_ins++;&#xD;
      //log.log("Delay: "+time_msg+" + "+outs[parseInt(message[1])]+" = "+(time_msg - outs[parseInt(message[1])])+"\n");&#xD;
      //log.log(""+parseInt(message[1])+";"+id+";"+(time_msg - outs[parseInt(message[1])])+"\n");&#xD;
      tfdelay.write(""+parseInt(message[1])+";"+id+";"+(time_msg - outs[parseInt(message[1])])+ ";" + parseInt(message[2]) + "\n");&#xD;
    }else if (message[0]=="Duplicates") {&#xD;
      tfduplicates.write(""+id+";"+parseInt(message[1])+"\n");&#xD;
    }else if (message[0]=="Received duplicate") {&#xD;
      tfraw_duplicates.write((time_msg_seconds/60|0) + ":" + (time_msg_seconds % 60).toFixed(3) + ";ID:" + id + ";" + msg + "\n");&#xD;
    }&#xD;
  } else if (message.length == 8) {&#xD;
    if (message[0] != "n") {&#xD;
      pdr += parseInt(message[0]);&#xD;
      total_subscribed++;&#xD;
    }&#xD;
    frame_tx += parseInt(message[1]);&#xD;
    msg_tx += parseInt(message[2]);&#xD;
    rx_time += parseInt(message[3]);&#xD;
    tx_time += parseInt(message[4]);&#xD;
    lpm_time += parseInt(message[5]);&#xD;
    cpu_time += parseInt(message[6]);&#xD;
    total_nodes++;&#xD;
    tfraw.write((time_msg_seconds/60|0) + ":" + (time_msg_seconds % 60).toFixed(3) + ";ID:" + id + ";" + id + ";" + msg + "\n");&#xD;
  }&#xD;
}</script>
      <active>true</active>
    </plugin_config>
    <width>600</width>
    <z>5</z>
    <height>700</height>
    <location_x>410</location_x>
    <location_y>82</location_y>
  </plugin>
  <plugin>
    org.contikios.cooja.plugins.TimeLine
    <plugin_config>
      <mote>0</mote>
      <mote>1</mote>
      <mote>2</mote>
      <mote>3</mote>
      <mote>4</mote>
      <mote>5</mote>
      <mote>6</mote>
      <mote>7</mote>
      <mote>8</mote>
      <mote>9</mote>
      <mote>10</mote>
      <mote>11</mote>
      <mote>12</mote>
      <showRadioRXTX />
      <showRadioHW />
      <showLEDs />
      <zoomfactor>500.0</zoomfactor>
    </plugin_config>
    <width>1710</width>
    <z>3</z>
    <height>198</height>
    <location_x>0</location_x>
    <location_y>796</location_y>
  </plugin>
</simconf>

