/*
 * SerialUsartCommunication.h
 *
 *  Created on: Aug 1, 2025
 *      Author: Amin Hassani
 */
#include "malloc.h"
#include "main.h"
#include "string"
#include "iostream"
#include "algorithm"
#include "functional"
#ifndef SRC_SERIALUSARTCOMMUNICATION_H_
#define SRC_SERIALUSARTCOMMUNICATION_H_

class SerialUsartCommunication {
	//template <typename,T>
public:

	static UART_HandleTypeDef* USART_HANDLER;
	static uint8_t* reciveBuffer;
	static int8_t RCV_BUFF_SIZE;
	static uint8_t* receiveCompleted();
	SerialUsartCommunication();
	SerialUsartCommunication(UART_HandleTypeDef*);
	//void intHandler(void);
    void send(std::string , int8_t);
    void recieve(uint8_t);
    void IrecieveAngle();
	virtual ~SerialUsartCommunication();
private:

    static std::function<int16_t()> interPerter;
	void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart);
	//uint8_t RCV_IDX,RCV_BYTE;
protected:


};

#endif /* SRC_SERIALUSARTCOMMUNICATION_H_ */
