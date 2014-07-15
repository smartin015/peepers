class RFControl
{
  public: 
    
    RFControl(){
      Mirf.spi = &MirfHardwareSpi;
      Mirf.init();
      Mirf.setRADDR((byte *)RF_ADDRESS);
      Mirf.payload = DATA_LEN;
      Mirf.config();
    }
    
  private:
    byte data[DATA_LEN];
    
    void rf_wait_for_cmd(){
      while (true) {
        if(!Mirf.isSending() && Mirf.dataReady()){
          Serial.println("Got packet");
          Mirf.getData(data);
          // TODO: ACK?
          return;
        }
      }
    }
    
    byte rf_cmd_type() {
      return data[0];
    }
    
    unsigned int rf_cmd_val(int index) {
      return data[index];
    }
    
    boolean rf_check_for_cmd() {
      if(!Mirf.isSending() && Mirf.dataReady()){
          Serial.println("Got packet");
          Mirf.getData(data);
          Serial.println("Command received");
          switch (rf_cmd_type()) {
            case CMD_QUACK:
              
              break;
            case CMD_RGB:
              
              break;
            case CMD_LASER:
              
              break;
            case CMD_LED_BAR:
              
              break;
            case CMD_SERVO:
              
              break;
            case CMD_ARC:
              
              break;
            default:
              Serial.println("INVALID_CMD");
          }
          return true;
        }
      return false;
    }
};

