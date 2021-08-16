#include "mbed.h"

#include "C12832.h"
#include "Sht31.h"


#define MAX_SIZE_NOME 10
#define NUM_PLANTAS   7

#define PWM_NIVEL_0 0
#define PWM_NIVEL_1 0.1
#define PWM_NIVEL_2 0.25
#define PWM_NIVEL_3 0.5
#define PWM_NIVEL_4 0.8
#define PWM_NIVEL_5 1

//void guarda_plantas();

static char lista_nomes[NUM_PLANTAS][MAX_SIZE_NOME] = {"Abacaxi",
                                                       "Banana",
                                                       "Goiaba",
                                                       "Laranja",
                                                       "Manga",
                                                       "Mamao",
                                                       "Uva"};
static float lista_temp_max[NUM_PLANTAS] = {14, 14, 12, 7.2, 12, 12, 2.2};



C12832 lcd(SPI_MOSI, SPI_SCK, SPI_MISO, p8, p11);
Sht31 sht31(I2C_SDA, I2C_SCL);
DigitalOut led(LED1);

PwmOut aquecedor(p25);


InterruptIn btn_troca(p29);
InterruptIn btn_temp(p30);

Ticker t1;
Ticker t2;

static short plant_select;
static short conta_leituras;
static float acum_leituras;
static bool leitura_celsius;

void botao_troca() {
    printf("Botao troca\n");
    plant_select++;
    if(plant_select >= NUM_PLANTAS)
    {
        plant_select = 0;
    }
}

void troca_celsos_firenite() {
    leitura_celsius = !leitura_celsius;
    printf("Troca °C e °F\n");
}

void seta_pwm(float temp)
{
    if((lista_temp_max[plant_select] - temp) > 8)
    {
        aquecedor = PWM_NIVEL_5;
    } else if((lista_temp_max[plant_select] - temp) > 6)
    {
        aquecedor = PWM_NIVEL_4;
    } else if((lista_temp_max[plant_select] - temp) > 4)
    {
        aquecedor = PWM_NIVEL_3;
    } else if((lista_temp_max[plant_select] - temp) > 2)
    {
        aquecedor = PWM_NIVEL_2;
    } else if((lista_temp_max[plant_select] - temp) > 0)
    {
        aquecedor = PWM_NIVEL_1;
    } else
    {
        aquecedor = PWM_NIVEL_0;
    }
}
void print_tela_principal(float temp)
{
    lcd.cls();
    lcd.locate(3, 3);
// lcd.printf("%s", lista_nomes[plant_select]);
    lcd.printf("%s \t  T_max: %.1f C", lista_nomes[plant_select], lista_temp_max[plant_select]);
    lcd.locate(3, 13);
    if(leitura_celsius)
    {
        lcd.printf("Temperatura: %.2f C", temp);  
    }else
    {
        lcd.printf("Temperatura: %.2f F", temp*(9.0/5.0) + 32);
    }
    lcd.locate(3, 23);
    lcd.printf("Duty Cycle: %.2f\n", aquecedor.read());
}

void le_temp() 
{
    float temp = sht31.readTemperature();
    acum_leituras += temp;
    conta_leituras++;
}

void atua_temp()
{
    float media_temp;
    media_temp = acum_leituras/conta_leituras;
    acum_leituras = 0;
    conta_leituras = 0;
    seta_pwm(media_temp);
    print_tela_principal(media_temp);
}

int main() {
    printf("Estufa Das Verdinhas\n");
    plant_select = 0;
    conta_leituras = 0;
    acum_leituras = 0;
    leitura_celsius = true;
    t1.attach(callback(&le_temp), 0.0250f);
    t2.attach(callback(&atua_temp), 0.5f);
    btn_troca.fall(callback(&botao_troca));
    btn_temp.fall(callback(&troca_celsos_firenite));    
    wait_ms(osWaitForever);
}