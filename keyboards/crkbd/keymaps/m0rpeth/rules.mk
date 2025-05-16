SRC += features/achordion.c

OLED_ENABLE = yes
OLED_TIMEOUT = 0
OLED_DRIVER = ssd1306

MOUSEKEY_ENABLE = no
CONSOLE_ENABLE = no
COMMAND_ENABLE = no
SLEEP_LED_ENABLE = no
AUDIO_ENABLE = no
BOOTMAGIC_ENABLE = yes
LEADER_ENABLE = no

# Backlight: Single color, per key, not individually addressable (all leds on or all leds off)
# RGBLight: Underglow RGB, linear design (single chain), individually addressable
# LED Matrix: Single color, per key, individually addressable
# RGB Matrix: RGB, per key, individually addressable
# Indicators: Scroll/Caps/Num Lock LEDs

RGBLIGHT_SUPPORTED = no
RGB_MATRIX_SUPPORTED = no

#COMBO_ENABLE = yes

