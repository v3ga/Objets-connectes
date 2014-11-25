  void runAppendRowChoreo(int RFID) 
{
  // Create the Choreo object using your Temboo session
  AppendRow appendRowChoreo = new AppendRow(session);

  // Set inputs
  appendRowChoreo.setUsername("####");
  appendRowChoreo.setPassword("####");

  if (RFID == 148)
  {
    appendRowChoreo.setRowData("visiteur,-1,-1");
  }
  else if (RFID == 67)
  {
    appendRowChoreo.setRowData("-1,-1,personnel");
  }
  else if (RFID == 36)
  {
    appendRowChoreo.setRowData("-1,residant,-1");
  }


  appendRowChoreo.setSpreadsheetTitle("seniorconnecte");

  // Run the Choreo and store the results
  AppendRowResultSet appendRowResults = appendRowChoreo.run();
  
  // Print results
  println(appendRowResults.getResponse());
  println(appendRowResults.getNewAccessToken());

}
