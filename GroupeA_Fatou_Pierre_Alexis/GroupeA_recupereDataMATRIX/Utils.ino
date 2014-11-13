String csvGetValue(String data, char separator, int index)
{
  int found = 0;
  int strIndex[] = {0, -1};
  int maxIndex = data.length()-1;

  for(int i=0; i<=maxIndex && found<=index; i++){
    if(data.charAt(i)==separator || i==maxIndex){
        found++;
        strIndex[0] = strIndex[1]+1;
        strIndex[1] = (i == maxIndex) ? i+1 : i;
    }
  }

  return found>index ? data.substring(strIndex[0], strIndex[1]) : "";
}

String csvGetRow(String data, int index)
{
  return csvGetValue(data, '\n', index);
}

String csvGetRowCell(String data, int indexRow, int indexColumn)
{
  String dataRow = csvGetRow(data, indexRow);
  if (!dataRow.equals(""))
    return csvGetValue(dataRow, ',', indexColumn);
  else return "";
}

int csvGetRowNb(String data)
{
  int nb = 0;
  String dataRow = "";
  do
  {
    dataRow = csvGetValue(data, '\n', nb);
    dataRow.trim();
    // Serial.println("["+String(nb)+"] "+dataRow);
    nb++;
  } while(!dataRow.equals(""));
  if (nb>0) nb--;
  return nb;
}

