/*-----------------------------------------------------------------------------------
*   FWMA_Filter.h
*   ȫ�ƣ�Fractional Weighted Moving Average Filter
*   ���ƣ���ʽ��Ȩ�ƶ�ƽ���˲���
*   2023-4-25   Ver1.0.0
*   By Simgor001 https://blog.simgor.cn
*   Copyright (C) 2023 Simgor001
*------------------------------------------------------------------------------------
*   # ����
*   - ����һ���򵥵��˲��⣬ͨ������ȡ��ֵ�˲�
*   - �����������֧�ּ������˲���
*   - ��ע�⣬�����˲���ʽ���ͺ��ԣ�ʵʱ�Ժܲ�ʺ��¶ȼ�������ʹ��
*
*   # ʹ������
*   - ���ö��г���FWMA_LEN
*   - ����FWMA_Init���������ô洢��ַ�Ͳ���
*   - �����Ҫʹ���������˲����������FWMA_filter����
*   - �����ʹ����ֵ�˲��������FWMA_median����
*
*   # ����˵��
*   �����¼��ֲ�����
*   - FWMA_LEN�����г��ȣ�Ĭ��Ϊ5��
*   - pres���ϴν��Ȩ
*   - af��˥��ϵ��
*   - data_min�����ݷ�Χ��Сֵ
*   - data_max�����ݷ�Χ���ֵ
*
*   ## pres
*   �ϴν��Ȩ������ǰһ�μ������Ե�ǰ��������Ӱ��̶ȣ�
*   ֵԽ��ǰһ�μ������Ե�ǰ�����Ӱ��Խ�󣬷�ӦԽ��������Խƽ��
*
*   ## af
*   ˥��ϵ������ֵԽС���������������������ݵı仯��
*   ����������ȥ��Ч�����ܻή�͡�
*   ��С��˥��ϵ����������Ҫ������Ӧ��ʵʱӦ�á�
*
*   # ��ʼ������
*   ``` c
*   FWMA_InitTypeDef FWMA_InitStruct;
*   FWMA_InitStruct.data_max = 2.5;
*   FWMA_InitStruct.data_min = 0;
*   FWMA_InitStruct.pres = 1;
*   FWMA_InitStruct.af = 2;
*   FWMA_t FWMA_s;
*   double FWMA_fifo[FWMA_LEN] = {0};
*   double FWMA_buf[3] = {0};
*
*   FWMA_Init(&FWMA_s, FWMA_fifo, FWMA_buf, &FWMA_InitStruct);
*   ```
*------------------------------------------------------------------------------------
*   The MIT License (MIT)
*
*   Copyright (C) 2023 Simgor001
*
*   Permission is hereby granted, free of charge, to any person obtaining a copy
*   of this software and associated documentation files (the "Software"), to deal
*   in the Software without restriction, including without limitation the rights
*   to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
*   copies of the Software, and to permit persons to whom the Software is
*   furnished to do so, subject to the following conditions:
*
*   The above copyright notice and this permission notice shall be included in all
*   copies or substantial portions of the Software.
*
*   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
*   IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
*   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
*   AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
*   LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
*   OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
*   SOFTWARE.
*-----------------------------------------------------------------------------------*/
/*==================================================================
 *     ����оƬͷ�ļ�
 * ===============================================================*/
//CH32ϵ��
#include "debug.h"
//STM32F103ϵ��
//#include "stm32f10x.h"

/*==================================================================
 *     ������ͷ�ļ�
 * ===============================================================*/
#ifndef _FWMA_FILTER_H_
#define _FWMA_FILTER_H_
#include "stdint.h"

/* ���г��� */
#define FWMA_LEN ((uint32_t)(5))

typedef struct
{
    double pres;            /* �ϴν��Ȩ */
    double af;              /* ˥��ϵ�� */
    double data_min;        /* ���뷶Χ��Сֵ */
    double data_max;        /* ���뷶Χ���ֵ */
}FWMA_InitTypeDef;

typedef struct
{
    double* FIFO;           /* �б� */
    uint32_t pos;           /* ��ǰλ�� */
    uint32_t len;           /* ���� */
    double avg_pre;         /* ��һ�ε�ת����� */
    uint32_t cnt;           /* ������� */
    double* buf;            /* ������ */
    FWMA_InitTypeDef param;
} FWMA_t;

/**
 * @brief ��ʼ��FWMA
 * @param FWMA_p ָ�� FWMA_t �ṹ���ָ�룬�൱�ھ��
 * @param List ָ�� FIFO �б��ָ�룬�˲����̵����ݱ��浽����
 * @param buf ָ�򻺳�����ָ��
 * @param FWMA_InitStruct ָ�� FWMA_InitTypeDef ��ָ�룬��ʼ������
 * @return �޷���ֵ
 */
void FWMA_Init(FWMA_t* FWMA_p, double* List, double* buf, FWMA_InitTypeDef* FWMA_InitStruct);

/**
 * @brief ��λ���˲�
 * @param FWMA_p �˲������
 * @param dat ����ӵ�����
 * @return �˲����ֵ
 */
double FWMA_median(FWMA_t* FWMA_p, double dat);

/**
 * @brief FWMA�˲�
 * @param FWMA_p �˲������
 * @param dat ����ӵ�����
 * @return �˲����ֵ
 */
double FWMA_filter(FWMA_t* FWMA_p, double dat);

#endif /* _FWMA_FILTER_H_ */
