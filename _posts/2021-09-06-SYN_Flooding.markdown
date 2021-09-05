---
layout: post
title:  "SYN Flooding"
description: Dos/DDOS SYN Flooding.
date:   2021-09-06 03:38:36 +0530
categories: Network Hacking
---
SYN Flooding 공격은 TCP의 연결 과정인 3-way Handshake 문제점을 악용하는 것이다.



![](https://github.com/hackintoanetwork/hackintoanetwork.github.io/blob/main/_posts/img/SYN-Flooding-02/3-way-handshake.png)

**[사진 1] TCP 3-way Handshake (TCP 연결 절차)**

**TCP 연결 설정 과정**

**1단계.** 두 시스템이 통신 하기 전에 클라이언트는 포트가 닫힌 Closed 상태이고, 서버는 해당 포트로 항상 서비스를 제공할 수 있는 Listen 상태이다.

**2단계.** 클라이언트가 처음 통신을 하려면 임의의 포트 번호가 클라이언트 프로그램에 할당되고, 클라이언트는 서버에 연결하고 싶다는 의사 표시로 SYN Sent 상태

(연결 요청 SYN 패킷을 보냄)가 된다.

**3단계.** 클라이언트의 연결 요청을 받은 서버는 SYN Received 상태가 되고, 클라이언트에 연결을 해도 좋다는 의미로 SYN+ACK 패킷을 보낸다.

**4단계.** 마지막으로 클라이언트는 연결을 요청한 것에 대한 서버의 응답을 확인했다는 표시로 ACK 패킷을 서버로 보낸다.



앞에서 TCP에 대한 최초 연결 시 클라이언트가 SYN 패킷을 보내고 이를 받은 서버는 SYN+ACK 패킷을 받는다고

설명했다. 마지막으로 클라이언트가 서버에 다시 ACK 패킷을 보내야 연결이 되는데 보내지 않는다면 어떻게 될까?



서버는 클라이언트가 ACK 패킷을 보낼때까지 SYN Received 상태로 일정 시간을 기다려야 하고, 그동안 공격자는 가상의 클라이언트로 위조한 SYN 패킷을 수 없이 

만들고 서버에 보내어 서버의 가용 동시 접속자 수를 모두 SYN Received 상태로 만들 수 있다.

이것이 SYN Flooding 공격의 기본 원리 이다.



## **실습**



![](https://github.com/hackintoanetwork/hackintoanetwork.github.io/blob/main/_posts/img/SYN-Flooding-02/hping3.PNG)

**[그림 2] 공격 수행**

```sudo hping3 -S -a 192.168.0.12 192.168.0.2 -p 80 --flood```

-S : SYN Flag로 설정

-a 192.168.0.2 : Source IP 

192.168.0.2 : Target IP

-p 80 : 80 Port 지정

--flood : 패킷 전송을 빠르게 보냄



![](https://github.com/hackintoanetwork/hackintoanetwork.github.io/blob/main/_posts/img/SYN-Flooding-02/SYN-Flag.PNG)

**[그림 3]  Wireshark 패킷 확인**

Wireshark를 통해 확인해보면 80번 Port로 SYN Flag를 무수히 보낸 것을 확인할 수 있다.



## **대응방안**



1. **침입 방지 시스템(IPS)과 같은 보안 시스템을 이용한다.**

   


2. **SYN backlog사이즈 증가시킨다. (한정적)**

  

tcp_max_syn_backlog 파일을 통해 현재 서버의 백로그큐 값을 확인

```cat /proc/sys/net/ipv4/tcp_max_syn_backlog```

```1024```

1024 보다 작으면 아래 명령어로 1024 이상으로 설정해줍니다.

```sysctl -w net.ipv4.tcp_max_syn_backlog=1024```



3. **TCP_Syncookies를 사용한다.**

   

**TCP_syncookies란?**

3Way-Handshake에서 호스트가 다른 호스트로부터 SYN을 받게되면  syn backlog를 저장하지않고, 

3wayhandshake가 연결 되었을때만 listen backlog에 저장한다.

syn 빈도가 많으면 무시해버린다.

**tcp_syncookies 활성화**

tcp_syncookies의 값을 0으로 바꾼다.

```echo "0" > /proc/sys/net/ipv4/tcp_syncookies```

​    

