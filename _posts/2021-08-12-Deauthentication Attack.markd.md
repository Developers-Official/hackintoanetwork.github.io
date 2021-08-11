---
layout: post
title:  "Deauthentication Attack"
description: Wi-Fi Deauthentication Attack.
date:   2021-08-12 03:038:36 +0530
categories: Network Hacking
---
A Wi-Fi deauthentication attack is a type of denial-of-service attack that targets communication between a user and a Wi-Fi wireless access point.



**Deauthentication Attack**은 사용자와 Wi-Fi 무선 액세스 포인트 간의 통신을 대상으로 하는 서비스 거부 공격(Dos attack)의 일종이고, 

**Deauthentication Attack**은 **Deauthentication frame**을 지속적으로 전송함으로써 **AP**와 **Station** 간의 **연결을 강제로 해제**시키는 공격이다.

 여기서, **공유기를 AP(Access Point)**라고 하고 **공유기에 연결되는 장치들을 Station**이라고 한다.

![](https://github.com/hackintoanetwork/hackintoanetwork.github.io/blob/main/_posts/img/Deauthentication%20Attack-Post-01/Post-01-img%201.PNG?raw=true)

**[그림 1] deauthentication attack 수행 이전의 무선망 상황**

AP와 3개의 장치들이 연결되어 있고 공격자는 무선랜카드를 통하여 무선 통신망의 통신 상황을 살펴보고 있다.

![](https://github.com/hackintoanetwork/hackintoanetwork.github.io/blob/main/_posts/img/Deauthentication%20Attack-Post-01/Post-01-img%202.PNG?raw=true)

**[그림 2] deauthentication attack 수행**

공격자는 AP를 가장한 Deauthentication frame을 반복적으로 *브로드캐스팅하여 공격을 수행한다.*

(브로드캐스팅(broadcasting)은 송신 호스트가 전송한 데이터가 네트워크에 연결된 모든 호스트에 전송되는 방식을 의미한다.)

![](https://github.com/hackintoanetwork/hackintoanetwork.github.io/blob/main/_posts/img/Deauthentication%20Attack-Post-01/Post-01-img%203.PNG?raw=true)

**[그림 3] AP와의 연결 끊어짐**

디바이스들은 공격 초기에는 재연결을 일정 횟수 수행한다. 

하지만 지속적으로 수신되는 Deauthentication frame으로 인해 재연결을 포기하게 되고 결국 연결이 해제된다. 

공격자가 Deauthentication frame를 전송하는 동안에는 장치들이 AP와 연결되지 않는다.

여기까지는 deauthentication attack이 이루어지는 과정이었고,

 

### 이제 공격 진행 과정을 실습을 통하여 살펴보겠다.



**aircrack-ng**의 포함된 툴 **Aireplay-ng**는 한 줄 명령을 실행하여 Deauthentication Attack을 실행할 수 있다.                                          MDK3, Void11, Scapy 및 Zulu 소프트웨어도 **Deauthentication Attack**을 탑재할 수 있지만 편의를 위해                                                            **Aireplay-ng**을 이용하여 실습을 해보겠다.

​    

공격자는 가상머신을 통해 만든 **Kali Linux 2021.2**, 공격 대상은 **개인 AP**(개인 공유기),

피해자는 AP에 연결된 **iphone XR ios 14.6**으로 설정하였다.

​    

랜카드는 **ALFA Network Inc.**사의 **AWUS1900** 모델을 사용하였고

해당 **랜카드의 칩셋**은 **Realtek RTL8814AU**로 <u>모니터 모드를 정식으로 지원하는 모델은 아니지만</u>, 

패치를 통해 **모니터 모드**와 **패킷 인젝션**을 가능하게 하였다.



![](https://github.com/hackintoanetwork/hackintoanetwork.github.io/blob/main/_posts/img/Deauthentication%20Attack-Post-01/Post-01-img%204.PNG?raw=true)

**[그림 4] 무선랜을 통해 확인하는 AP와 station**

```airodump-ng wlan0```

![](https://github.com/hackintoanetwork/hackintoanetwork.github.io/blob/main/_posts/img/Deauthentication%20Attack-Post-01/Post-01-img%205.PNG?raw=true)

  **[그림 5] 타겟 AP에 연결된 station**

```airodump-ng --bssid 00:26:66:66:29:A8 –c 13 wlan0```

![](https://github.com/hackintoanetwork/hackintoanetwork.github.io/blob/main/_posts/img/Deauthentication%20Attack-Post-01/Post-01-img%206.png?raw=true)

**[그림 6] Deauthentication Attack 수행 모습**

```aireplay-ng --deauth 100 –a 00:26:66:66:29:A8 wlan0```

해당 공격을 통하여 AP에 연결된 station들은 강제적으로 연결이 해제된다. 

**station은 재연결을 시도**하겠지만 **Deauthentication frame**이 지속적으로 수신되기 때문에 **재연결을 포기하고 연결이 해제**되게 된다. 



![](https://github.com/hackintoanetwork/hackintoanetwork.github.io/blob/main/_posts/img/Deauthentication%20Attack-Post-01/Post-01-img%207.jpg?raw=true)

**[그림 7] AP와 연결 시 문제 발생**

AP와 연결 시 **문제**가 **발생**하는 모습을 볼 수 있다. **성공적으로 공격이 수행**되는 것을 확인할 수 있다.

​    

​    

## **Deauthentication Attack의 활용**



### **Evil twin 공격 (Evil twin access points)**

해킹 커뮤니티에서 사용되는 인증 해제의 주요 목적 중 하나는 클라이언트를 악의적인 **트윈 액세스 포인트**에 연결하도록 강제하는 것이다. 그러면 클라이언트와 액세스 포인트 간에 전송되는 **네트워크 패킷을 캡처**하는 데 사용할 수 있다.

공격자는 대상 클라이언트에 대한 **Deauthentication Attack**을 수행하여 대상 클라이언트의 현재 네트워크와의 연결을 끊고 클라이언트가 **악의적인 트윈 액세스 포인트에 자동으로 연결**할 수 있도록 한다.

​    

### **와이파이 패스워드 크래킹(Password attacks)**

**WPA** 또는 **WPA2**가 활성화된 WiFi 사용자에 대한 **무차별 대입 공격 (BruteForce Attack)** 또는 **사전 기반 WPA 암호 크래킹 공격**

**(Dictionany Attack)**을 시작하려면 해커가 먼저 **WPA 4-Way Handshake**를 **스니핑(Sniffing)**해야 한다. 

이때 공격자는 **Deauthentication Attack**으로 정상 사용자를 강제 연결 해제시켜 **WPA 4-Way Handshake**를 스니핑 유도할 수 있다.

**WPA 4-Way Handshake****를 스니핑에 성공한다면 공격자는**무차별 대입 공격 (BruteForce Attack)**또는**사전 기반 WPA 암호 크래킹 공격 (Dictionany Attack)**을 수행하여 **무선 AP**의 **패스워드**를 **크랙** 할 수 있을 것이다.

​    

​    

​    