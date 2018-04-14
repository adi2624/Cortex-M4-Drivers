#include "hal_spi_driver.h"
#include<stdint.h>


static void hal_spi_configure_phase_and_polarity(SPI_TypeDef *SPIx, uint32_t phase_value, uint32_t polarity)
{
	if(phase_value)
	{
		SPIx->CR1 |= SPI_REG_CR1_CPHA;		//Clock phase =1
	}
	else
	{
		SPIx->CR1 &= ~SPI_REG_CR1_CPHA;		//clock phase =0
	}
	
	if(polarity)
	{
		SPIx->CR1 |= SPI_REG_CR1_CPOL;		//polarity=1
		
	}
	else
	{
		SPIx->CR1  &= ~SPI_REG_CR1_CPOL;	//polarity=0
	}
}
static void hal_spi_enable(SPI_TypeDef *SPIx)
{
	if(!(SPIx->CR1 & SPI_REG_CR1_SPE))
		SPIx->CR1 |= SPI_REG_CR1_SPE;
}
static void hal_spi_disable(SPI_TypeDef *SPIx)
{
	SPIx->CR1 &= ~SPI_REG_CR1_SPE;
}
static void hal_spi_configure_datasize_direction(SPI_TypeDef *SPIx, uint32_t datasize_16, uint32_t lsbfirst)
{
	if(datasize_16)
	{
		SPIx->CR1 |= SPI_REG_CR1_DFF;			//enable 16 bit data frame format.
		
	}
	else
	{
		SPIx->CR1 &= ~SPI_REG_CR1_DFF;
	}
	
	if(lsbfirst)
	{
		SPIx->CR1 |= SPI_CR1_LSBFIRST;
	}
	else
	{
		SPIx->CR1 &= ~SPI_CR1_LSBFIRST;
	}
}

static void hal_spi_configure_nss_master(SPI_TypeDef *SPIx, uint32_t ssm_enable)
{
	if(ssm_enable)
	{
		SPIx->CR1 |= SPI_REG_CR1_SSM;
		SPIx->CR1 |= SPI_REG_CR1_SSI;			//master's nss pins need to be set high to disable the pin.
	}
	else
	{
		SPIx->CR1 &= ~SPI_REG_CR1_SSM;
		
	}
	
}
static void hal_spi_configure_nss_slave(SPI_TypeDef *SPIx, uint32_t ssm_enable)
{
	if(ssm_enable)
	{
		SPIx->CR1 |= SPI_REG_CR1_SSM;
	}
	else
	{
		SPIx->CR1 &= ~SPI_REG_CR1_SSM;
	}
}

static void hal_spi_configure_device_mode(SPI_TypeDef *SPIx, uint32_t master)
{
	if(master)
	{
		SPIx->CR1 |= SPI_REG_CR1_MSTR;
	}
	else
	{
		SPIx->CR1 &= ~SPI_REG_CR1_MSTR;
	}
}
void hal_spi_enable_txe_interrupt(SPI_TypeDef *SPIx)
{
	SPIx->CR2 |= SPI_REG_CR2_TXEIE_ENABLE;
}
static void hal_spi_enable_rxne_interrupt(SPI_TypeDef *SPIx)

{

	SPIx->CR2 |= SPI_REG_CR2_RXNEIE_ENABLE;
}

static void hal_spi_disable_rxne_interrupt(SPI_TypeDef *SPIx)

{
	SPIx->CR2 &= ~SPI_REG_CR2_RXNEIE_ENABLE;
}
void hal_spi_init(spi_handle_t *spi_handle)
{
	
}
void hal_spi_master_tx(spi_handle_t *spi_handle,uint8_t *buffer,uint32_t len)
{
	spi_handle->pTxBuffPtr = buffer;
	spi_handle->TxXferCount = len;
	spi_handle->TxXferSize = len;
	
	spi_handle->State = HAL_SPI_STATE_BUSY_TX;
	hal_spi_enable(spi_handle->Instance);
	hal_spi_enable_txe_interrupt(spi_handle->Instance);
	
}
void hal_spi_slave_rx(spi_handle_t *spi_handle, uint8_t *rcv_buffer, uint32_t len)
{
	spi_handle->pTxBuffPtr = rcv_buffer;
	spi_handle->TxXferCount = len;
	spi_handle->TxXferSize = len;
	
	spi_handle->State = HAL_SPI_STATE_BUSY_RX;
	hal_spi_enable(spi_handle->Instance);
	hal_spi_enable_rxne_interrupt(spi_handle->Instance);
}
void hal_spi_master_rx(spi_handle_t *spi_handle, uint8_t *rx_buffer, uint32_t len)
{
	uint32_t i=0, val;
	//dummy bits to be sent before reading.
	spi_handle->pTxBuffPtr = rx_buffer;
	spi_handle->TxXferCount =len;
	spi_handle->TxXferSize =len;
	
	//Actual data is read here.
	spi_handle->pRxBuffPtr = rx_buffer;
	spi_handle->RxXferCount =len;
	spi_handle->RxXferSize = len;
	
	
	spi_handle->State = HAL_SPI_STATE_BUSY_RX;
	
	hal_spi_enable(spi_handle->Instance);
	
	val=  spi_handle->Instance->DR;
	
	hal_spi_enable_rxne_interrupt(spi_handle->Instance);
	hal_spi_enable_txe_interrupt(spi_handle->Instance);
	
	
	
}
void hal_spi_slave_tx(spi_handle_t *spi_handle, uint8_t *tx_buffer, uint32_t len)
{
	spi_handle->pTxBuffPtr = tx_buffer;
	spi_handle-> TxXferSize = len;
	spi_handle -> TxXferCount =len;
	
	
	//DUMMY RX FROM MASTER TO SLAVE
	spi_handle->pRxBuffPtr = tx_buffer;
	spi_handle->RxXferSize = len;
	spi_handle->RxXferCount = len;
	
	spi_handle->State = HAL_SPI_STATE_BUSY_TX;
	
	hal_spi_enable(spi_handle->Instance);
	
	hal_spi_enable_rxne_interrupt(spi_handle->Instance);
	hal_spi_enable_txe_interrupt(spi_handle->Instance);
	
	 
}
void hal_i2c_spi_irq_handler(spi_handle_t *hspi);