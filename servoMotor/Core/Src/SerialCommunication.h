#ifndef SERIAL_COMMUNICATION
#define SERIAL_COMMUNICATION

#include <functional>
#include <cinttypes>
#include "main.h"
#include "string"



template <typename ReturnType>
class SerialCommunication
{
public:
	static UART_HandleTypeDef* USART_HANDLER;
	static uint8_t* reciveBuffer;
	static int8_t RCV_BUFF_SIZE;
    SerialCommunication(UART_HandleTypeDef*,std::function<ReturnType(const uint8_t*, size_t)> processor);
    void send(std::string , int8_t);
    void receiveData(const uint8_t* data, size_t size);

private:
    std::function<ReturnType(const uint8_t*, size_t)> processor_;
};

#endif // SERIAL_COMMUNICATION
