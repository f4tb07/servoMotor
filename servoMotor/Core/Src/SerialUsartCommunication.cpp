/*
 * SerialUsartCommunication.cpp
 *
 *  Created on: Aug 1, 2025
 *      Author: Amin Hassani
 */

#include "SerialUsartCommunication.h"
#include "string.h"
#include "stdio.h"
//#include "stm32g0xx_hal_uart.h"

UART_HandleTypeDef* SerialUsartCommunication::USART_HANDLER ;
uint8_t* SerialUsartCommunication::reciveBuffer;
int8_t SerialUsartCommunication::RCV_BUFF_SIZE ;
uint8_t rcvByte[2];
int rcvIdx=0;
//template <typename T>
// = IrecieveAngle();


SerialUsartCommunication::SerialUsartCommunication()
{
	// TODO Auto-generated constructor stub

}

SerialUsartCommunication::SerialUsartCommunication(
		UART_HandleTypeDef* usartHandle)
{
	USART_HANDLER = usartHandle;

}



void SerialUsartCommunication::send(std::string message, int8_t timeOut)
{
	uint8_t* tmpCharMemPtr = (uint8_t*) malloc(message.size()+1);

    for(int i=0;i<static_cast<int>(message.size());i++)
    {
    	tmpCharMemPtr[i]=message[i];
    }
    tmpCharMemPtr[message.size()]='\0';
    HAL_UART_Transmit(USART_HANDLER, tmpCharMemPtr, message.size(),timeOut);
    free(tmpCharMemPtr);
}


void echo( int8_t timeOut)
{
	uint8_t* tmpCharMemPtr = (uint8_t*) malloc(SerialUsartCommunication::RCV_BUFF_SIZE);
	memcpy(tmpCharMemPtr,SerialUsartCommunication::reciveBuffer,SerialUsartCommunication::RCV_BUFF_SIZE);
    HAL_UART_Transmit(SerialUsartCommunication::USART_HANDLER, tmpCharMemPtr, SerialUsartCommunication::RCV_BUFF_SIZE,timeOut);
    free(tmpCharMemPtr);
}


extern "C"
{

	void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
	{

		    memcpy(SerialUsartCommunication::reciveBuffer+rcvIdx,rcvByte,1);
		    if(HAL_UART_Receive_IT(SerialUsartCommunication::USART_HANDLER,rcvByte ,1)!= HAL_BUSY && ++rcvIdx>=SerialUsartCommunication::RCV_BUFF_SIZE)
		    		    {
		    		    	SerialUsartCommunication::receiveCompleted ();
		    				//receiveCompleted ();
		    		    	rcvIdx=0;
		    		    }


	}
}

void SerialUsartCommunication::recieve(uint8_t rcvBuffSize)
{

	if(rcvBuffSize>0)
		{
		RCV_BUFF_SIZE = rcvBuffSize;
		reciveBuffer = 	(uint8_t*) malloc(rcvBuffSize);
					if(!reciveBuffer)
						delete this;
		}
		rcvIdx=0;
		HAL_UART_Receive_IT(USART_HANDLER, rcvByte, 1);
}
void SerialUsartCommunication::IrecieveAngle()
{
	   recieve(5);
       auto myLmabda = [this]()->int16_t
		{
			int16_t angle;
			uint8_t* tmpCharMemPtr = (uint8_t*) malloc(this->RCV_BUFF_SIZE);
			memcpy(tmpCharMemPtr,this->reciveBuffer,this->RCV_BUFF_SIZE);
			free(this->reciveBuffer);
			if(tmpCharMemPtr[0]=='<' && tmpCharMemPtr[this->RCV_BUFF_SIZE-1]=='>')
			    {
			    	int16_t hunderd=tmpCharMemPtr[1]*100;
			    	int16_t ten=tmpCharMemPtr[2]*10;
			    	angle = hunderd + ten + tmpCharMemPtr[3];
			    }
			return angle;
		};
     std::function<int16_t()> interPerter=myLmabda;
}

uint8_t* SerialUsartCommunication::receiveCompleted ( )
{

	if(rcvIdx>=RCV_BUFF_SIZE )
		{
		     HAL_UART_AbortReceive(USART_HANDLER);
             int16_t ang= interPerter();
			 return reciveBuffer; //here we have a mem allocation which is not freed. And must mange
		}
	else
		return 0;
}
//template <typename T>
//std::function<T()> genericInterpreter;





SerialUsartCommunication::~SerialUsartCommunication() {
	// TODO Auto-generated destructor stub
}

