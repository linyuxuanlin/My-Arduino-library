#include<U8glib.h>
U8GLIB_SSD1306_128X64 u8g(10, 9, 12, 11, 13);
//D0-10,D1-9,RST-13,DC-11


void draw(void) {
  // graphic commands to redraw the complete screen should be placed here  
  u8g.setFont(u8g_font_unifont);
  //u8g.setFont(u8g_font_osb21);
  u8g.drawStr( 20, 20, "Hello Lin!");

  u8g.drawFrame(1, 1, 126, 62); 
  
}

void setup(void) {
  
  // flip screen, if required
  // u8g.setRot180();
  
  // set SPI backup if required
  //u8g.setHardwareBackup(u8g_backup_avr_spi);

 
    u8g.setColorIndex(1);         
}

void loop(void) {
  // picture loop
  u8g.firstPage();  
  do {
    draw();
  } while( u8g.nextPage() );
  
  // rebuild the picture after some delay
  delay(500);
}
