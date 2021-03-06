void receiveData(boolean routingOrAodv)
{
    byte data[32];
    int state = radio.receive(data, 32);
    if(state == ERR_NONE){  
      
    // packet was successfully received
    Serial.println(F("received success!"));
    // print the data of the packet
    Serial.print(F("Data: "));
    Serial.println(data[32]);
    
    parseData(data,",");
    if(!routingOrAodv)
    {
      parseNodeBefore(valSplit[4],">");//cari node terakhir
      cekDest(ID);
    }
    else
    {
      cekDestAodv(ID);
    }
  }
}
void parseData(char text[], String key)
{
  String dataString = String(text);
  int countSplitSecond=0;
  int lastIndexSecond=0;
  for(int j = 0; j < dataString.length(); j++)
  {
    if(dataString.substring(j, j+1) == key)
    {
      valSplit[countSplitSecond] = dataString.substring(lastIndexSecond,j);
      lastIndexSecond = j + 1;
      //Serial.print(countSplitSecond);
      //Serial.print(":");
      //Serial.println(valSplit[countSplitSecond]);
      countSplitSecond++;
    }
  }
}
void cekDest(int myId)
{
  if(valSplit[2] == String(myId))
  {
    if(valSplit[0] == "P")
    {
      Serial.println("Received RREP");
      tableRouting();
      Serial.println();
    }
    else
    {
      //Serial.println("Got RREQ");
    }
  }
  
}
void cekDestAodv(int myId)
{
  if(valSplit[2] == String(myId))
  {
    if(valSplit[0] == "V")
    {
      Serial.println("Received AODV");
      showFromNodeData();
      Serial.println();
    }
    else
    {
      //Serial.println("Got RREQ");
    }
  }
  
}
