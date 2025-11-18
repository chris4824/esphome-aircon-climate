#pragma once

#include "esphome/core/component.h"
#include "esphome/components/climate/climate.h"
#include "esphome/components/sensor/sensor.h"
#include "esphome/components/uart/uart.h"

namespace esphome {
namespace aircon_climate {

#pragma pack(1)
typedef struct _Device_Status {
  // Keep your exact struct — it’s perfect
  uint8_t header[16];
  uint8_t wind_status;
  uint8_t sleep_status;
  uint8_t direction_status : 2;
  uint8_t run_status : 2;
  uint8_t mode_status : 4;
  uint8_t indoor_temperature_setting;
  uint8_t indoor_temperature_status;
  uint8_t indoor_pipe_temperature;
  int8_t indoor_humidity_setting;
  int8_t indoor_humidity_status;
  uint8_t somatosensory_temperature;
  uint8_t somatosensory_compensation_ctrl : 3;
  uint8_t somatosensory_compensation : 5;
  uint8_t temperature_Fahrenheit : 3;
  uint8_t temperature_compensation : 5;
  uint8_t timer;
  uint8_t hour;
  uint8_t minute;
  uint8_t poweron_hour;
  uint8_t poweron_minute;
  uint8_t poweroff_hour;
  uint8_t poweroff_minute;
  uint8_t wind_door : 4;
  uint8_t drying : 4;
  uint8_t dual_frequency : 1;
  uint8_t efficient : 1;
  uint8_t low_electricity : 1;
  uint8_t low_power : 1;
  uint8_t heat : 1;
  uint8_t nature : 1;
  uint8_t left_right : 1;
  uint8_t up_down : 1;
  uint8_t smoke : 1;
  uint8_t voice : 1;
  uint8_t mute : 1;
  uint8_t smart_eye : 1;
  uint8_t outdoor_clear : 1;
  uint8_t indoor_clear : 1;
  uint8_t swap : 1;
  uint8_t dew : 1;
  uint8_t indoor_electric : 1;
  uint8_t right_wind : 1;
  uint8_t left_wind : 1;
  uint8_t filter_reset : 1;
  uint8_t indoor_led : 1;
  uint8_t indicate_led : 1;
  uint8_t display_led : 1;
  uint8_t back_led : 1;
  uint8_t indoor_eeprom : 1;
  uint8_t sample : 1;
  uint8_t rev23 : 4;
  uint8_t time_lapse : 1;
  uint8_t auto_check : 1;
  uint8_t indoor_outdoor_communication : 1;
  uint8_t indoor_zero_voltage : 1;
  uint8_t indoor_bars : 1;
  uint8_t indoor_machine_run : 1;
  uint8_t indoor_water_pump : 1;
  uint8_t indoor_humidity_sensor : 1;
  uint8_t indoor_temperature_pipe_sensor : 1;
  uint8_t indoor_temperature_sensor : 1;
  uint8_t rev25 : 3;
  uint8_t eeprom_communication : 1;
  uint8_t electric_communication : 1;
  uint8_t keypad_communication : 1;
  uint8_t display_communication : 1;
  uint8_t compressor_frequency;
  uint8_t compressor_frequency_setting;
  uint8_t compressor_frequency_send;
  int8_t outdoor_temperature;
  int8_t outdoor_condenser_temperature;
  int8_t compressor_exhaust_temperature;
  int8_t target_exhaust_temperature;
  uint8_t expand_threshold;
  uint8_t UAB_HIGH;
  uint8_t UAB_LOW;
  uint8_t UBC_HIGH;
  uint8_t UBC_LOW;
  uint8_t UCA_HIGH;
  uint8_t UCA_LOW;
  uint8_t IAB;
  uint8_t IBC;
  uint8_t ICA;
  uint8_t generatrix_voltage_high;
  uint8_t generatrix_voltage_low;
  uint8_t IUV;
  uint8_t wind_machine : 3;
  uint8_t outdoor_machine : 1;
  uint8_t four_way : 1;
  uint8_t rev46 : 3;
  uint8_t rev47;
  uint8_t rev48;
  uint8_t rev49;
  uint8_t rev50;
  uint8_t rev51;
  uint8_t rev52;
  uint8_t rev53;
  uint8_t rev54;
  uint8_t rev55;
  uint8_t rev56;
  uint8_t extra[6];
  uint16_t chk_sum;
  uint8_t foooter[2];
} Device_Status;
#pragma pack()

class AirconClimate : public climate::Climate, public uart::UARTDevice, public Component {
 public:
  void setup() override;
  void loop() override;
  void update() override;
  void control(const climate::ClimateCall &call) override;
  climate::ClimateTraits traits() override;

  // Sensors that Python code will assign
  sensor::Sensor *compressor_frequency{nullptr};
  sensor::Sensor *compressor_frequency_setting{nullptr};
  sensor::Sensor *compressor_frequency_send{nullptr};
  sensor::Sensor *outdoor_temperature{nullptr};
  sensor::Sensor *outdoor_condenser_temperature{nullptr};
  sensor::Sensor *compressor_exhaust_temperature{nullptr};
  sensor::Sensor *target_exhaust_temperature{nullptr};
  sensor::Sensor *indoor_pipe_temperature{nullptr};
  sensor::Sensor *indoor_humidity_setting{nullptr};
  sensor::Sensor *indoor_humidity_status{nullptr};

 protected:
  float heat_tgt_temp = 21.0f;
  float cool_tgt_temp = 24.0f;

  static const int UART_BUF_SIZE = 128;
  uint8_t uart_buf[UART_BUF_SIZE]{};
  bool wait_for_rx = false;

  int get_response(uint8_t input, uint8_t *out);
  void blocking_send(const uint8_t *buf, size_t sz);
  void request_update();
  void set_sensor(sensor::Sensor *sensor, float value);
  void set_temp(float temp);
};

}  // namespace aircon_climate
}  // namespace esphome