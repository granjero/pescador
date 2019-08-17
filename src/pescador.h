



// Valores para el DNS captivePortal
const byte DNS_PORT = 53;

// Valores de la funcion softAPConfig
IPAddress local_IP(192,168,4,1);
IPAddress gateway(192,168,4,1);
IPAddress subnet(255,255,255,0);

// Estamos pescando?
bool pescando = false;

// SSID a Pescar
String ssid_a_pescar = "";

/********************
        HTML
*********************/

// PAGINAS DISPONIBLES
void    handleRoot();
void    handleAPescar();
void    handlePescando();
void    handlePique();
void    handleInfo();
void    handleEeprom();
void    handleEepromDelete();

// FUNCIONES HTML
String  listaWiFiHTML();
int     calidadSenial(int RSSI);

// Codigo HTML para servir
const char HTML_Head[] PROGMEM                  = "<!DOCTYPE html><html lang=\"en\"> <head> <meta charset=\"UTF-8\" name=\"viewport\" content=\"width=device-width, initial-scale=1, user-scalable=no\"/> <title>Pescador</title>";
const char HTML_Style[] PROGMEM                 = "<style> h1 {font-size: 3em;} </style>";
const char HTML_Style_Root[] PROGMEM            = "<style>.c{text-align: center;} div,input{padding:5px;font-size:1em;} input{width:75%;} body{text-align: center;font-family:verdana;} button{border:0;border-radius:0.3rem;background-color:#1fa3ec;color:#fff;line-height:2.4rem;font-size:1.2rem;width:76%;} .q{float: right;width: 64px;text-align: right;} .l{background: url(\"data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAACAAAAAgCAMAAABEpIrGAAAALVBMVEX///8EBwfBwsLw8PAzNjaCg4NTVVUjJiZDRUUUFxdiZGSho6OSk5Pg4eFydHTCjaf3AAAAZElEQVQ4je2NSw7AIAhEBamKn97/uMXEGBvozkWb9C2Zx4xzWykBhFAeYp9gkLyZE0zIMno9n4g19hmdY39scwqVkOXaxph0ZCXQcqxSpgQpONa59wkRDOL93eAXvimwlbPbwwVAegLS1HGfZAAAAABJRU5ErkJggg==\") no-repeat left center;background-size: 1em;}</style>";
const char HTML_Head_end[] PROGMEM              = "</head> <body> ";
const char HTML_end[] PROGMEM                   = "</body> </html>";

const char HTML_Formulario[] PROGMEM            = "<form method=\"get\" action=\"pescando\" id=\"f\" >";
const char HTML_Formulario_end[] PROGMEM        = "</form>";

const char HTML_Formulario_Root[] PROGMEM       = "<p>Para navegar ingrese la contraseña:</p><form method=\"get\" action=\"pique\" id=\"f\" > <input <input id='p' name='p' length=64 type='password' placeholder='contraseña'> <br/> </form> <br /> <button type=\"submit\" form=\"f\" value=\"conectar\"> Conectar </button> ";
//const char HTML_Formulario_Root_end[] PROGMEM   = "</form>";
//const char HTML_Input_Root[] PROGMEM            = "<input <input id='p' name='p' length=64 type='password' placeholder='password'><br/>";

const char BOTON_Pescar[] PROGMEM               = "<br /> <button type=\"submit\" form=\"f\" value=\"Pescar\"> A Pescar </button> ";
/********************
        /HTML
*********************/
