"""Aircon Climate external component."""
import esphome.codegen as cg
from esphome.components import climate

# Namespace for the component
aircon_climate_ns = cg.esphome_ns_namespace("aircon_climate")

# Import the class (defined in climate.py or here)
AirconClimate = aircon_climate_ns.class_(
    "AirconClimate", climate.Climate, cg.Component
)