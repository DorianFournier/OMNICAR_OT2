/*
 * MY_NRF24.h
 *
 *  Created on: Jun 10, 2021
 *      Author: TEAM OMNICAR
 */

#ifndef INC_OMNICAR_INC_MY_NRF24_H_
#define INC_OMNICAR_INC_MY_NRF24_H_

//List of header files
#include <omnicar_inc/nRF24L01.h>
#include "stm32f4xx_hal.h"   			//** Change this according to your STM32 series **//
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

//**** TypeDefs ****//
//1. Power Amplifier function, NRF24_setPALevel()
typedef enum {
	RF24_PA_m18dB = 0,
	RF24_PA_m12dB,
	RF24_PA_m6dB,
	RF24_PA_0dB,
	RF24_PA_ERROR
}rf24_pa_dbm_e ;
//2. NRF24_setDataRate() input
typedef enum {
	RF24_1MBPS = 0,
	RF24_2MBPS,
	RF24_250KBPS
}rf24_datarate_e;
//3. NRF24_setCRCLength() input
typedef enum {
	RF24_CRC_DISABLED = 0,
	RF24_CRC_8,
	RF24_CRC_16
}rf24_crclength_e;
//4. Pipe address registers
static const uint8_t NRF24_ADDR_REGS[7] = {
		REG_RX_ADDR_P0,
		REG_RX_ADDR_P1,
		REG_RX_ADDR_P2,
		REG_RX_ADDR_P3,
		REG_RX_ADDR_P4,
		REG_RX_ADDR_P5,
		REG_TX_ADDR
};
//5. RX_PW_Px registers addresses
static const uint8_t RF24_RX_PW_PIPE[6] = {
		REG_RX_PW_P0,
		REG_RX_PW_P1,
		REG_RX_PW_P2,
		REG_RX_PW_P3,
		REG_RX_PW_P4,
		REG_RX_PW_P5
};
//**** Functions prototypes ****//
//Microsecond delay function
void NRF24_DelayMicroSeconds(uint32_t uSec);																				//OK

//1. Chip Select function
void NRF24_csn(int mode);																									//OK
//2. Chip Enable
void NRF24_ce(int level);																									//OK
//3. Read single byte from a register
uint8_t NRF24_read_register(uint8_t reg);																					//OK
//4. Read multiple bytes register
void NRF24_read_registerN(uint8_t reg, uint8_t *buf, uint8_t len);															//OK
//5. Write single byte register
void NRF24_write_register(uint8_t reg, uint8_t value);																		//OK
//6. Write multipl bytes register
void NRF24_write_registerN(uint8_t reg, const uint8_t* buf, uint8_t len);													//OK
//7. Write transmit payload
void NRF24_write_payload(const void* buf, uint8_t len);																		//OK
//8. Read receive payload
void NRF24_read_payload(void* buf, uint8_t len);																			//OK
//9. Flush Tx buffer
void NRF24_flush_tx(void);																									//OK
//10. Flush Rx buffer
void NRF24_flush_rx(void);																									//OK
//11. Get status register value
uint8_t NRF24_get_status(void);																								//OK

//12. Begin function
void NRF24_begin(GPIO_TypeDef *nrf24PORT, uint16_t nrfCSN_Pin, uint16_t nrfCE_Pin, SPI_HandleTypeDef nrfSPI);				//OK
//13. Listen on open pipes for reading (Must call NRF24_openReadingPipe() first)
void NRF24_startListening(void);																							//RX
//14. Stop listening (essential before any write operation)
void NRF24_stopListening(void);																								//OK TX

//15. Write(Transmit data), returns true if successfully sent
bool NRF24_write( const void* buf, uint8_t len );																			//OK
//16. Check for available data to read
bool NRF24_available(void);																									//OK
//17. Read received data
bool NRF24_read( void* buf, uint8_t len );
//18. Open Tx pipe for writing (Cannot perform this while Listenning, has to call NRF24_stopListening)
void NRF24_openWritingPipe(uint64_t address);																				//OK
//19. Open reading pipe
void NRF24_openReadingPipe(uint8_t number, uint64_t address);																//RX
//20 set transmit retries (rf24_Retries_e) and delay
void NRF24_setRetries(uint8_t delay, uint8_t count);																		//OK
//21. Set RF channel frequency
void NRF24_setChannel(uint8_t channel);																						//OK
//22. Set payload size
void NRF24_setPayloadSize(uint8_t size);																					//OK

//24. Get dynamic payload size, of latest packet received
uint8_t NRF24_getDynamicPayloadSize(void);																					//OK
//25. Enable payload on Ackknowledge packet
void NRF24_enableAckPayload(void);																							//OK
//26. Enable dynamic payloads
void NRF24_enableDynamicPayloads(void);																						//OK
void NRF24_disableDynamicPayloads(void);																					//OK

//28. Set Auto Ack for all
void NRF24_setAutoAck(bool enable);																							//OK
//29. Set Auto Ack for certain pipe
void NRF24_setAutoAckPipe( uint8_t pipe, bool enable ) ;												// OHHHH ?
//30. Set transmit power level
void NRF24_setPALevel( rf24_pa_dbm_e level ) ;																				//OK

//32. Set data rate (250 Kbps, 1Mbps, 2Mbps)
bool NRF24_setDataRate(rf24_datarate_e speed);																				//OK

//34. Set crc length (disable, 8-bits or 16-bits)
void NRF24_setCRCLength(rf24_crclength_e length);																			//OK
//37. power up
void NRF24_powerUp(void) ;																					// ?????
//38. power down
void NRF24_powerDown(void);																									//OK
//39. Check if data are available and on which pipe (Use this for multiple rx pipes)
bool NRF24_availablePipe(uint8_t* pipe_num);
//40. Start write (for IRQ mode)
void NRF24_startWrite( const void* buf, uint8_t len );																		//OK
//41. Write acknowledge payload
void NRF24_writeAckPayload(uint8_t pipe, const void* buf, uint8_t len);
//42. Check if an Ack payload is available
bool NRF24_isAckPayloadAvailable(void);																		// OHHHHHH ?
//43. Check interrupt flags
void NRF24_whatHappened(bool *tx_ok,bool *tx_fail,bool *rx_ready);															//OK WITH IRQ

//46. Reset Status
void NRF24_resetStatus(void);																								//OK
//47. ACTIVATE cmd
void NRF24_ACTIVATE_cmd(void);																								//OK

//**********  Dorian Fournier - Functions **********//

void NRF24_transmitInit(uint64_t add,uint8_t channel, uint8_t payload_size);												//OK
void NRF24_dataTransmission(uint8_t *tab_Tx, uint8_t tab_Tx_size, uint8_t *tab_Ack, uint8_t tab_Ack_size);					//OK

void printSETUPAWReg(void);																									//OK DEBUG
void printRF_SETUPReg(void);//OK DEBUG
void printCONFIGReg(void);
//******** Delete **********//

//48. Get AckPayload Size
uint8_t NRF24_GetAckPayloadSize(void);
//44. Test if there is a carrier on the previous listenning period (useful to check for intereference)
bool NRF24_testCarrier(void);
//45. Test if a signal carrier exists (=> -64dB), only for NRF24L01+
bool NRF24_testRPD(void) ;
//27. Check if module is NRF24L01+ or normal module
bool NRF24_isNRF_Plus(void) ;
//36. Disable CRC
void NRF24_disableCRC( void ) ;
//35. Get CRC length
rf24_crclength_e NRF24_getCRCLength(void);
//33. Get data rate
rf24_datarate_e NRF24_getDataRate( void );
//31. Get transmit power level
rf24_pa_dbm_e NRF24_getPALevel( void ) ;
//23. Get payload size
uint8_t NRF24_getPayloadSize(void);



#endif /* INC_OMNICAR_INC_MY_NRF24_H_ */
