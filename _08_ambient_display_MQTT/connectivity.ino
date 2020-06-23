void connect() {
  // this is a patch for the timers that has to be corrected later
  long timerConnect = millis();

  Serial.print("checking wifi...");
  while (WiFi.status() != WL_CONNECTED) {
    if (millis() - timerConnect > 1000) {
      Serial.print(".");
      oppositeScrolls();
      updateRings();
      pixels.show();
      delay(10);

      timerConnect = millis();
    }
  }

  // add a Wifi connected event here
  //XXX

  Serial.print("\nconnecting...");
  while (!client.connect("arduino", "try", "try")) {
    if (millis() - timerConnect > 1000) {
      Serial.print(".");
      oppositeScrolls();
      updateRings();
      pixels.show();
      timerConnect = millis();
    }
  }

  // add an MQTT connected event here
  //XXX

  Serial.println("\nconnected!");

  client.onMessage(messageReceived);
  client.subscribe("IoTaP-lab/Linuxcomputer");
  // client.unsubscribe("/example");
}

void messageReceived(String &topic, String &payload) {
  Serial.print("incoming: ");
  Serial.print(topic);
  Serial.print(" - ");
  Serial.print(payload);
  Serial.println();
}
