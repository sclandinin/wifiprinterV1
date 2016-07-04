//prototypes

void port_init();
void sleep_all();
void get_weather();
void get_wordoftheday();

//lcd functions
void lcd_init();
void send_command(char command);
void send_data(char data);
void send_string(char string[],int length);
char reverse_bits(char value);

//wifi functions
void serial_init();
int wifi_connect();
void wifi_acknowledge();
void wifi_close();
void wifi_skip_data();

void weather_start();
void temp_read(char temp[]);
void wind_read(char wind[]);

void word_start();
void word_read(char word[]);
void definition_read(char definition[]);
void partOfSpeech_read(char partOfSpeech[]);

//parsing code
int find_temp();
void get_temp(char temp[]);
int find_wind();
void get_wind(char wind[]);

//printer functions
int _user_putc (char c);
void printerTest();
void paperCheck();
char printerRead();

//delay functions
void delay();
void delaylcd();
void delaywifi();
void delaywifi2();


