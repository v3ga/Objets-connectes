class LCDRowDisplay
{
  int pos;
  String s,s2;
  boolean needScroll;
  int delta;
  int row;
  
  LCDRowDisplay()
  {
    row = 0;
    pos=0;
    s = "";
    needScroll = false;
    if (s.length()>16)
    {
      needScroll = true;
      delta = s.length()-16;
    }
  }
  
  void set(int row_, String s_)
  {
    row = row_;
    s = s_;  
  }
  
  void update()
  {
    if (needScroll)
    {
      s2 = s.substring(pos,pos+16);
      pos+=1;
      if (pos>=delta)
      {
         pos = 0;
      }
    }
    lcd.setCursor(0,row);
    lcd.print(s2);
  }
  
};
