void ajoutePersonnePassee(String nom)
{
  // Pas trouvée!
  if (personnesPassees.indexOf(nom) == -1)
  {
    if (personnesNb==0)
      personnesPassees = nom;
    else
      personnesPassees += ","+nom;
  } 

  personnesNb += 1;  
}

void changeState(int newState)
{  
  if (state == 0)
  {
    if (newState == 1)
    {
      state = 1;
      drawInfos();
      delay(4000);
    }
  }
  else
    if (state == 1)
    {
      if (newState == 0)
      {
        personnesPassees = "";
        personnesNb=0;
        state = 0;
      }  
      else
      {
        personnesPassees = "";
        personnesNb=0;
        drawInfos();
      }
    }



}


void drawInfos()
{
  lcd.clear();
  if (personnesNb>0)
  {
    lcd.setCursor(0, 0);
    lcd.print(String(personnesNb)+" visite(s)");           
    lcd.setCursor(0, 1);
    lcd.print(personnesPassees);
  }
  else{
    lcd.setCursor(0, 0);
    lcd.print("personne :-(");           
  }
}



