#include "usart_printf.h"
#include "stdio.h"
#include "usart.h"
/******************************************************************************************/
/* �������´���, ֧��printf����, ������Ҫѡ��use MicroLIB */

#if USART_PRINTF_EN
#if (__ARMCC_VERSION >= 6010050)                    /* ʹ��AC6������ʱ */
__asm(".global __use_no_semihosting\n\t");          /* ������ʹ�ð�����ģʽ */
__asm(".global __ARM_use_no_argv \n\t");            /* AC6����Ҫ����main����Ϊ�޲�����ʽ�����򲿷����̿��ܳ��ְ�����ģʽ */

#else
/* ʹ��AC5������ʱ, Ҫ�����ﶨ��__FILE �� ��ʹ�ð�����ģʽ */
#pragma import(__use_no_semihosting)

struct __FILE
{
    int handle;
    /* Whatever you require here. If the only file you are using is */
    /* standard output using printf() for debugging, no file handling */
    /* is required. */
};

#endif

/* ��ʹ�ð�����ģʽ��������Ҫ�ض���_ttywrch\_sys_exit\_sys_command_string����,��ͬʱ����AC6��AC5ģʽ */
int _ttywrch(int ch)
{
    ch = ch;
    return ch;
}

/* ����_sys_exit()�Ա���ʹ�ð�����ģʽ */
void _sys_exit(int x)
{
    x = x;
}

char *_sys_command_string(char *cmd, int len)
{
    return NULL;
}

/* FILE �� stdio.h���涨��. */
FILE __stdout;

// /* �ض���fputc����, printf�������ջ�ͨ������fputc����ַ��������� */
// int fputc(int ch, FILE *f)
// {
//     while ((USART2->SR & 0X40) == 0);               /* �ȴ���һ���ַ�������� */

//     USART2->DR = (uint8_t)ch;                       /* ��Ҫ���͵��ַ� ch д�뵽DR�Ĵ��� */
//     return ch;
// }

int fputc(int ch, FILE *f)
{
    /* ����һ���ֽ����ݵ�����DEBUG_USART */
    HAL_UART_Transmit(&huart2, (uint8_t *)&ch, 1, 1000);
 
    return (ch);
}
#endif
/***********************************************END*******************************************/