#include "bq27427.h"

static esp_err_t read_control_word(i2c_dev_t *dev, uint16_t *function, uint16_t *data);

static const char *TAG = "bq27427";

#define I2C_FREQ_HZ 400000 

#define CHECK(x) do { esp_err_t __; if ((__ = x) != ESP_OK) return __; } while (0)
#define CHECK_ARG(VAL) do { if (!(VAL)) return ESP_ERR_INVALID_ARG; } while (0)

esp_err_t bq27427_init_desc(i2c_dev_t *dev, i2c_port_t port, gpio_num_t sda_gpio, gpio_num_t scl_gpio);
{
    CHECK_ARG(dev);

    dev->port = port;
    dev->addr = BQ27427_I2C_ADDRESS;
    dev->cfg.sda_io_num = sda_gpio;
    dev->cfg.scl_io_num = scl_gpio;
#if HELPER_TARGET_IS_ESP32
    dev->cfg.master.clk_speed = I2C_FREQ_HZ;
#endif
    return i2c_dev_create_mutex(dev);
}

esp_err_t bq27427_get_device_type(i2c_dev_t *dev, uint16_t *dev_type)
{
    CHECK_ARG(dev);

}
