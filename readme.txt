{\rtf1\ansi\ansicpg936\cocoartf1404\cocoasubrtf130
{\fonttbl\f0\fswiss\fcharset0 Helvetica;}
{\colortbl;\red255\green255\blue255;}
\paperw11900\paperh16840\margl1440\margr1440\vieww10800\viewh8400\viewkind0
\pard\tx566\tx1133\tx1700\tx2267\tx2834\tx3401\tx3968\tx4535\tx5102\tx5669\tx6236\tx6803\pardirnatural\partightenfactor0

\f0\fs24 \cf0 Introduction:\
This program is to simulate a stock trading system.\
\
There are two main programs, one is client_main and another is sever_main.\
\
The server_main will generate the new price every 10s and send it to the client after it start to run.\
It also receives the buy request from the client and decides whether the buying is successful or not by comparing the price between clients and the server. Moreover, the server will count the total number of attempt from clients. \
\
The client_main would receive the price from the server and display it to users.It also sends a buy request to server when the user click the key \'93return\'94. After receiving the result of buying from server, it will display it to users.\
\
Using Way:\
get into the directory and run the server_main first and then run the client_main. When staring running the client_main, please input the hostname and the port number.\
\
Warning:\
The server can only listen to at most 5 clients in this program so don\'92t run more than 5 clients at the same time!!!\
}