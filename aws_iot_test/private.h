#include <pgmspace.h>

#define SECRET
#define THINGNAME "chessBoard1"                

// Topics of MQTT
#define AWS_IOT_PUBLISH_TOPIC   "chessBoard1/moves"
#define AWS_IOT_SUBSCRIBE_TOPIC "chessBoard2/moves"

const char WIFI_SSID[] = "david";                                
const char WIFI_PASSWORD[] = "swordfish";                            
const char AWS_IOT_ENDPOINT[] = "a9lr3px6arz1a-ats.iot.us-east-2.amazonaws.com";        

// Amazon Root CA 1
static const char AWS_CERT_CA[] PROGMEM = R"EOF(
-----BEGIN CERTIFICATE-----
MIIDQTCCAimgAwIBAgITBmyfz5m/jAo54vB4ikPmljZbyjANBgkqhkiG9w0BAQsF
ADA5MQswCQYDVQQGEwJVUzEPMA0GA1UEChMGQW1hem9uMRkwFwYDVQQDExBBbWF6
b24gUm9vdCBDQSAxMB4XDTE1MDUyNjAwMDAwMFoXDTM4MDExNzAwMDAwMFowOTEL
MAkGA1UEBhMCVVMxDzANBgNVBAoTBkFtYXpvbjEZMBcGA1UEAxMQQW1hem9uIFJv
b3QgQ0EgMTCCASIwDQYJKoZIhvcNAQEBBQADggEPADCCAQoCggEBALJ4gHHKeNXj
ca9HgFB0fW7Y14h29Jlo91ghYPl0hAEvrAIthtOgQ3pOsqTQNroBvo3bSMgHFzZM
9O6II8c+6zf1tRn4SWiw3te5djgdYZ6k/oI2peVKVuRF4fn9tBb6dNqcmzU5L/qw
IFAGbHrQgLKm+a/sRxmPUDgH3KKHOVj4utWp+UhnMJbulHheb4mjUcAwhmahRWa6
VOujw5H5SNz/0egwLX0tdHA114gk957EWW67c4cX8jJGKLhD+rcdqsq08p8kDi1L
93FcXmn/6pUCyziKrlA4b9v7LWIbxcceVOF34GfID5yHI9Y/QCB/IIDEgEw+OyQm
jgSubJrIqg0CAwEAAaNCMEAwDwYDVR0TAQH/BAUwAwEB/zAOBgNVHQ8BAf8EBAMC
AYYwHQYDVR0OBBYEFIQYzIU07LwMlJQuCFmcx7IQTgoIMA0GCSqGSIb3DQEBCwUA
A4IBAQCY8jdaQZChGsV2USggNiMOruYou6r4lK5IpDB/G/wkjUu0yKGX9rbxenDI
U5PMCCjjmCXPI6T53iHTfIUJrU6adTrCC2qJeHZERxhlbI1Bjjt/msv0tadQ1wUs
N+gDS63pYaACbvXy8MWy7Vu33PqUXHeeE6V/Uq2V8viTO96LXFvKWlJbYK8U90vv
o/ufQJVtMVT8QtPHRh8jrdkPSHCa2XV4cdFyQzR1bldZwgJcJmApzyMZFo6IQ6XU
5MsI+yMRQ+hDKXJioaldXgjUkK642M4UwtBV8ob2xJNDd2ZhwLnoQdeXeGADbkpy
rqXRfboQnoZsG4q5WTP468SQvvG5
-----END CERTIFICATE-----
)EOF";

// Device Certificate                                          
static const char AWS_CERT_CRT[] PROGMEM = R"KEY(
-----BEGIN CERTIFICATE-----
MIIDWTCCAkGgAwIBAgIUIpnuqUkgBbr8F94YVq538oj2zz8wDQYJKoZIhvcNAQEL
BQAwTTFLMEkGA1UECwxCQW1hem9uIFdlYiBTZXJ2aWNlcyBPPUFtYXpvbi5jb20g
SW5jLiBMPVNlYXR0bGUgU1Q9V2FzaGluZ3RvbiBDPVVTMB4XDTIyMDMyNTEzMzYy
OVoXDTQ5MTIzMTIzNTk1OVowHjEcMBoGA1UEAwwTQVdTIElvVCBDZXJ0aWZpY2F0
ZTCCASIwDQYJKoZIhvcNAQEBBQADggEPADCCAQoCggEBANMq93WSLlbCAXIfT/NF
yvWJA3hak7/myi9BytJILDeaNQxJCMnGB9ks1NDYE68cxDiFn6XHreyGs7b1Os9Q
DMeqHyhf1+1kPMIE5eB4yl7trcK4ABcyAnUs/vj3fcMFE/zo3JTBo/xX/e9CGCLS
y3XzKn3Fv5LDtG5QKZXonqcO2TA1CnQyqU02ta+iIn85uV7IELgTWh+evGjlD0Ou
XzwrhYuTJV6NVjanh9eZFXjTYHc3oefrOKlXmAwyFZ59Infn3Yqutiwmvm02hy5F
jn0ymJxRQy9iT2pA91vC2Shk7gGFn54l9++dA1REx84gc/gHp+WkO/VbTlt2QECZ
lZkCAwEAAaNgMF4wHwYDVR0jBBgwFoAUvbc69aJ80ZXZjeabSQUBOnpv5vcwHQYD
VR0OBBYEFO5hMz6WKBK1vgsUYAH3LVREPQf2MAwGA1UdEwEB/wQCMAAwDgYDVR0P
AQH/BAQDAgeAMA0GCSqGSIb3DQEBCwUAA4IBAQCyOPBLdLjqc29co0ZSMJcXr0jk
y4eIj4yl6BXRKy6ZUPhRKMgQzdSn6WEHPFTTuerWj21tWMmYo1CT3AMSzVnDSBAF
Bg4A4HzbuGY3uD3FdvaUY9FNIIu8tmLKCQ3p1O0JYI4OzRDW3zmmPqvYhToI7Rea
daIPnNFhEODt1txeXiq7Tbxs1llKlpNT76TgVjJqeOrgIdqopf93eF176H9CJS9e
yg9av8GfotT2segdzNNetcz/SNyWkpRgn8ZAOFV0Lunv4H8Xj96ehC3YjgZPdkq+
gbdNPnTmC5iIc6gCiBsAx/vq+2nMvx7toIwda9ssDWmvB23IKUy6ea+CnS2Q
-----END CERTIFICATE-----

)KEY";

// Device Private Key                                              
static const char AWS_CERT_PRIVATE[] PROGMEM = R"KEY(
-----BEGIN RSA PRIVATE KEY-----
MIIEowIBAAKCAQEA0yr3dZIuVsIBch9P80XK9YkDeFqTv+bKL0HK0kgsN5o1DEkI
ycYH2SzU0NgTrxzEOIWfpcet7IaztvU6z1AMx6ofKF/X7WQ8wgTl4HjKXu2twrgA
FzICdSz++Pd9wwUT/OjclMGj/Ff970IYItLLdfMqfcW/ksO0blApleiepw7ZMDUK
dDKpTTa1r6Iifzm5XsgQuBNaH568aOUPQ65fPCuFi5MlXo1WNqeH15kVeNNgdzeh
5+s4qVeYDDIVnn0id+fdiq62LCa+bTaHLkWOfTKYnFFDL2JPakD3W8LZKGTuAYWf
niX3750DVETHziBz+Aen5aQ79VtOW3ZAQJmVmQIDAQABAoIBAFIIJ/d5YRz84rjl
pxZXL3/wyPNRJIJw8mwnP9YuiVbURfVOzeYsUtIwE0BKIGNvZl6asikhh9QRg/D4
FO+CJmTOFqqFiQlEXkH0yyRHaD42UMEK36YjHEdOwoIPCsDe0SP3hfEXxE98Ez6F
y4CDqNxaKVCQqFooQoh0BaOhqTg13KmBfGWp2sVAa9vK21roiYYqI6USDPdziupR
rv2cabv6mE4w6jHOk8bfcuxqj2Uqi8xMZkKPNw+xBySOsL3/SrGjWlhgSmyYAkEu
DGQvOxMi3FtJPGojcVpXm26E+Gu7EJc3Dm/U4muwV9CyJ0fu6m7/oEq+cHtf/JdH
5Exjj90CgYEA8feUvFzkdpKtOkPsilq0+KcteXFbLEcgFdDjqsXLV7za2MBJWr9l
kzUxdZVoeE5cJPgoxpgzl6csnVzONrHI7Xy1NMUt5/nQRc+/DOx9yZ2qhLP3iv/o
4Cs849BRKYDePCNbucZj7Nq8buH3U1uYNFduo+maM4aPtLz80EaIn48CgYEA32oe
B0oiBT9BkJ2Gzhy8nbzOTsPIBBSkEr2lkt/P6RiQ4DB2mr2irtSAVwTESgfdowSf
J+dWb/q3SJ5Wfn8j4AYl0ZbKHHgJjx3914dBvPxubnwrL6jlAIneXGJ24BWJhvVs
4VbQh9KnproO3tKJ/pcI0YXcaM4yMgvAXLzw5FcCgYAGyEbOBNiOjkv2vyKpOiOq
eJ0os0m38wJuOh23krXBbtS/kJw9w/Gn76zEO/ziqmegzafu8SM5FAGHI6vQEqms
Jnu5z/EaeIEjA9C6HwLjnNzDvXup1MSFTBD33cX4oNkZ3G/cxDfW0sbHYOQa3Q1m
IjFCvPCKkzICAe4gNGnt9wKBgCTNqlyxDaGnpflYudhCS6AAdkvrXIuvise7jgb/
75QKg/MqiJ89FguO3gV3t44qdYxhOoasSUTxHDhOPRlhgFtrJ9e661h9PbXhzusu
UNn9C4QP2F1liTPpgkPdxI9tfNZKn8EPOBLn1M5WYBS8wha6cq1xS7nIHeS4otuk
FFrJAoGBAOO+cQ1oN1gpLBHOw+GsT8qnTBkcaufSRGekglp1Ywb3VoYQf3Q9tuML
qxvathii4UDls8Er6Lr5Pr75SoVb38AhFQh8mJakOybORsQfJY9c30KJ87fSoURw
GJ/hkiE0qn3vI/NHeAZ4becS3xnKieByw410yrAy7DGUiNJS/oTy
-----END RSA PRIVATE KEY-----

)KEY";
