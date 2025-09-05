#include "SerialCommunication.h"

#include "stdio.h"
//#ifndef SERIAL_COMMUNICATION
//#define SERIAL_COMMUNICATION

template <typename ReturnType>
UART_HandleTypeDef* SerialCommunication<ReturnType>::USART_HANDLER ;
template <typename ReturnType>
uint8_t* SerialCommunication<ReturnType>::reciveBuffer;
template <typename ReturnType>
int8_t SerialCommunication<ReturnType>::RCV_BUFF_SIZE ;
uint8_t rcvbyte[2];//uint8_t rcvByte[2];
int rcvidx=0;//int rcvIdx=0;

template <typename ReturnType>
SerialCommunication<ReturnType>::SerialCommunication(UART_HandleTypeDef* usartHandle,std::function<ReturnType(const uint8_t*, size_t)> processor)
    : processor_(processor)
{
	USART_HANDLER = usartHandle;
}

template <typename ReturnType>
void SerialCommunication<ReturnType>::receiveData(const uint8_t* data, size_t size)
{
    ReturnType result = processor_(data, size);
    // Do something with the processed result...
}

template <typename ReturnType>
void SerialCommunication<ReturnType>::send(std::string message, int8_t timeOut)
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
template <typename ReturnType>
#ifdef __cplusplus
extern "C"
{
#endif
	void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
	{

		    memcpy(SerialCommunication<ReturnType>::reciveBuffer+rcvidx,rcvbyte,1);
		    if(HAL_UART_Receive_IT(SerialCommunication<ReturnType>::USART_HANDLER,rcvbyte ,1)!= HAL_BUSY && ++rcvidx>=SerialCommunication<ReturnType>::RCV_BUFF_SIZE)
		    		    {
		    	            SerialCommunication<ReturnType>::receiveCompleted ();
		    				//receiveCompleted ();
		    		    	rcvidx=0;
		    		    }


	}
#ifdef __cplusplus
}
#endif

//#endif // SERIAL_COMMUNICATION
