-- ======================================================================
-- RTD Design.ctl generated from RTD Design
-- 06/09/2017 at 11:51
-- This file is auto generated. ANY EDITS YOU MAKE MAY BE LOST WHEN THIS FILE IS REGENERATED!!!
-- ======================================================================

-- TopDesign
-- =============================================================================
-- The following directives assign pins to the locations specific for the
-- CY8CKIT-046 kit.
-- =============================================================================

-- === SPIM (SCB mode) ===
attribute port_location of \SPIS:miso_s(0)\ : label is "PORT(6,1)";
attribute port_location of \SPIS:mosi_s(0)\ : label is "PORT(6,0)";
attribute port_location of \SPIS:sclk_s(0)\ : label is "PORT(6,2)";
attribute port_location of \SPIS:ss0_s(0)\  : label is "PORT(6,3)";

-- === SPIM (UDB based) ===
attribute port_location of miso_m(0) : label is "PORT(2,1)";
attribute port_location of mosi_m(0) : label is "PORT(2,2)";
attribute port_location of sclk_m(0) : label is "PORT(2,0)";
attribute port_location of ss_m(0)   : label is "PORT(2,3)";

-- === RGB LED ===
attribute port_location of LED_RED(0)   : label is "PORT(5,2)"; -- RED LED
attribute port_location of LED_GREEN(0) : label is "PORT(5,3)"; -- GREEN LED
attribute port_location of LED_BLUE(0)  : label is "PORT(5,4)"; -- BLUE LED
-- PSoC Clock Editor
-- Directives Editor
-- Analog Device Editor
csattribute placement_force of \IDAC:cy_psoc4_idac\ : label is "F(CSIDAC8,1)";
