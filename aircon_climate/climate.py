import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import climate, uart
from esphome.const import (
    CONF_ID,
    CONF_UART_ID,
    UNIT_CELSIUS,
    UNIT_PERCENT,
    UNIT_HERTZ,
    STATE_CLASS_MEASUREMENT,
    DEVICE_CLASS_TEMPERATURE,
    DEVICE_CLASS_HUMIDITY,
    DEVICE_CLASS_FREQUENCY,
    ICON_THERMOMETER,
    ICON_WATER_PERCENT,
)
from . import aircon_climate_ns, AirconClimate

DEPENDENCIES = [uart.UARTComponent]

CONFIG_SCHEMA = cv.Schema(
    {
        cv.GenerateID(CONF_UART_ID): cv.use_id(uart.UARTComponent),
        cv.GenerateID(): cv.declare_id(AirconClimate),
    }
).extend(cv.CLIMATE_SCHEMA)

async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)
    uart_instance = await cg.get_variable(config[CONF_UART_ID])
    cg.add(var.set_uart(uart_instance))

    # Register the climate entity
    await climate.register_climate(var, config)

    # List of sensors to auto-expose as secondary values
    sensor_configs = [
        {
            "name": "Compressor Frequency",
            "key": "compressor_frequency",
            "unit": UNIT_HERTZ,
            "icon": "mdi:current-ac",
            "device_class": DEVICE_CLASS_FREQUENCY,
            "state_class": STATE_CLASS_MEASUREMENT,
        },
        {
            "name": "Compressor Frequency Setting",
            "key": "compressor_frequency_setting",
            "unit": UNIT_HERTZ,
            "icon": "mdi:current-ac",
            "device_class": DEVICE_CLASS_FREQUENCY,
            "state_class": STATE_CLASS_MEASUREMENT,
        },
        {
            "name": "Compressor Frequency Send",
            "key": "compressor_frequency_send",
            "unit": UNIT_HERTZ,
            "icon": "mdi:current-ac",
            "device_class": DEVICE_CLASS_FREQUENCY,
            "state_class": STATE_CLASS_MEASUREMENT,
        },
        {
            "name": "Outdoor Temperature",
            "key": "outdoor_temperature",
            "unit": UNIT_CELSIUS,
            "icon": ICON_THERMOMETER,
            "device_class": DEVICE_CLASS_TEMPERATURE,
            "state_class": STATE_CLASS_MEASUREMENT,
        },
        {
            "name": "Outdoor Condenser Temperature",
            "key": "outdoor_condenser_temperature",
            "unit": UNIT_CELSIUS,
            "icon": ICON_THERMOMETER,
            "device_class": DEVICE_CLASS_TEMPERATURE,
            "state_class": STATE_CLASS_MEASUREMENT,
        },
        {
            "name": "Compressor Exhaust Temperature",
            "key": "compressor_exhaust_temperature",
            "unit": UNIT_CELSIUS,
            "icon": ICON_THERMOMETER,
            "device_class": DEVICE_CLASS_TEMPERATURE,
            "state_class": STATE_CLASS_MEASUREMENT,
        },
        {
            "name": "Target Exhaust Temperature",
            "key": "target_exhaust_temperature",
            "unit": UNIT_CELSIUS,
            "icon": ICON_THERMOMETER,
            "device_class": DEVICE_CLASS_TEMPERATURE,
            "state_class": STATE_CLASS_MEASUREMENT,
        },
        {
            "name": "Indoor Pipe Temperature",
            "key": "indoor_pipe_temperature",
            "unit": UNIT_CELSIUS,
            "icon": ICON_THERMOMETER,
            "device_class": DEVICE_CLASS_TEMPERATURE,
            "state_class": STATE_CLASS_MEASUREMENT,
        },
        {
            "name": "Indoor Humidity Setting",
            "key": "indoor_humidity_setting",
            "unit": UNIT_PERCENT,
            "icon": ICON_WATER_PERCENT,
            "device_class": DEVICE_CLASS_HUMIDITY,
            "state_class": STATE_CLASS_MEASUREMENT,
        },
        {
            "name": "Indoor Humidity Status",
            "key": "indoor_humidity_status",
            "unit": UNIT_PERCENT,
            "icon": ICON_WATER_PERCENT,
            "device_class": DEVICE_CLASS_HUMIDITY,
            "state_class": STATE_CLASS_MEASUREMENT,
        },
    ]

    # Generate and assign sensor pointers
    for sens_config in sensor_configs:
        sens = await climate.new_climate_secondary_sensor(
            sens_config["name"], config
        )
        sens_var = cg.get_variable(sens)
        setter = getattr(var, f"set_{sens_config['key']}")
        cg.add(setter(sens_var))
        # Apply config to the sensor
        if "unit" in sens_config:
            cg.add(sens_var.set_unit_of_measurement(sens_config["unit"]))
        if "icon" in sens_config:
            cg.add(sens_var.set_icon(sens_config["icon"]))
        if "device_class" in sens_config:
            cg.add(sens_var.set_device_class(sens_config["device_class"]))
        if "state_class" in sens_config:
            cg.add(sens_var.set_state_class(sens_config["state_class"]))