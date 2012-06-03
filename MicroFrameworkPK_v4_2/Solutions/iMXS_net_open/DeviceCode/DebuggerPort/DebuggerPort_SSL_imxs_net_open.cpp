#include <tinyhal.h>
#include <com_decl.h>

static LPCSTR s_SelfSignedCert = 
"Bag Attributes\n\
    Microsoft Local Key set: <No Values>\n\
    localKeyID: 01 00 00 00 \n\
    friendlyName: 0dd0e399-f446-479e-97d5-f1c0e45b0580\n\
    Microsoft CSP Name: Microsoft RSA SChannel Cryptographic ProviderKey Attributes\n\
    X509v3 Key Usage: 10 \n\
-----BEGIN RSA PRIVATE KEY-----\n\
MIIEowIBAAKCAQEAzhgZTPwDKDvWdpEtt2AgAuwPzYC08hhcJa5piriazkhImcaL\n\
xxxV8yo1APLfzk7w9oNiPbNzk5/LSBNDBcMs1sXX9dihfuGKJmfuxgUg0dgXedbH\n\
0WC5s1JJPPVuuAaGxfH50js4UTYrWbnBLuZvDWr2Km6Msw3SQq7JYFVaI9NA1jiz\n\
n9SupTuh9ZuX8mqlUGME5bJAzeZHSG5WDBZQre74ZK5G8BQ4X1Bu9oMQWjojd00I\n\
VckLlRoiXn74co0Kiu8/r1yt7l1l1g+Dr0gx8jrbLxuA/fOjpj6NLSTUfHFyvxGi\n\
x50t1Ul6pAVsDcU5Ar+yT5/2vnumiBxC2bb4aQIDAQABAoIBAGFBkBb7SkYfTsqv\n\
IiLKMvEOEzsIRNuGUV3a26WCDlPQWqpuvqGcppbU0SR8eM80A5RhVegGGkGNA/Ik\n\
XNmITE2iGZLDwxpMNtR+8XfzDZTZY+K0T6FoAtozt6oTrEcdlVYuJZVnKuFwLa7u\n\
8NJAHiH32ukVOEJ7AEFFmHRkcuA6RSZUslY/iXIANLzwk+Yb2VnbeJd0f8wtXxOn\n\
OOVdsro4HIMddy7iyrALy4ZkcwjqinMQrDVlgZ0i1lFEtTp/9DaoAceDVI1e7Kv/\n\
tIBvFVobJIEN3dP9PV1aPH9i/DCDFT6LY1XmnXH3WWPp/uaBUIwIHJFONK2p8cPI\n\
bQycGgECgYEA6kbPttb7hACDpgGEw5+uZxcwXf5L7+3Do2Xg+Bvca1M0YydFanqf\n\
+zNNx+XyDV+rAsRGg36HZnw0m+yE+ZDRmtvCYeGvWiph0Wpju0imfk7XswNdQG9b\n\
v36gHfMlw980R8SPJjanAzXDVtFMRTDd9gLu96mtBb6jx+LMhf9HTKkCgYEA4TRM\n\
4S3rFwvG88HqkhSbJ2NZQTkXEqGH32JDoDybRbbRaArkUYZ/bOsPhxp/7nbEcME8\n\
rTwYklOjf+ezIrjMUym9PW4DLnYJjUtT1oE0vvoXNI1ujG4nLD01xjfwhDbmuBbS\n\
bqY4ANmLB23O8JuO/UqF63t8q/txVQJAE/Ur5cECgYEAqQxzseGrF/MvC8iovmgo\n\
9qaa9hgbP4P32Z4YGbAw+xjNAodB5bWaXy8D/yyD3vabdaGfqB7TITaa17Bxu4uu\n\
U+ojd3HckFlowC3ezTN9QEMwDjJtRaOVNrbuXu4m4BHdrbO9/7sMBJr0216nhH3g\n\
jDZNrVQ4T57im8eiAUbVchECgYA6JiD7u7mKF9ZlNlr1ITD2uKZhOvaELwVAXsUL\n\
aNrG42+qp7VQf6QDYaZ+wg7qaexLGPor2OqXTdVXv2H3wzOu/YYJiJB1vLC2tQ6O\n\
won2DelT/nje9cpTl/J8nhEScoKcYfgv7edkAMfvQSE/60q+iDGQHjCQz7nxs0UM\n\
Yi/VgQKBgBk8Bfz54ABM4vJBzObEfmwddibpMPQfDLRN/dsLM0dq3c90DJvaChl/\n\
aoZqtft8AlfoG7b2tw5zU9sv5WdnijSA7jmZgqewwtR+8FMtn66ioFP38BsNOtA/\n\
1Vye12Utvokk2vq2e5AfuCtz0zJ2sueM1SHSCyc7vy3M7vlxpoRy\n\
-----END RSA PRIVATE KEY-----\n\
Bag Attributes\n\
    localKeyID: 01 00 00 00 \n\
    friendlyName: NetMF SSL Sample Cert\n\
subject=/CN=ZACHL-SBA1.redmond.corp.microsoft.com\n\
issuer=/CN=ZACHL-SBA1.redmond.corp.microsoft.com\n\
-----BEGIN CERTIFICATE-----\n\
MIIDDjCCAfagAwIBAgIQJW80M/b8bphIa2Sv6/gFmzANBgkqhkiG9w0BAQUFADAw\n\
MS4wLAYDVQQDEyVaQUNITC1TQkExLnJlZG1vbmQuY29ycC5taWNyb3NvZnQuY29t\n\
MB4XDTExMDQyMDE4MzkwMloXDTEyMDQyMDAwMDAwMFowMDEuMCwGA1UEAxMlWkFD\n\
SEwtU0JBMS5yZWRtb25kLmNvcnAubWljcm9zb2Z0LmNvbTCCASIwDQYJKoZIhvcN\n\
AQEBBQADggEPADCCAQoCggEBAM4YGUz8Ayg71naRLbdgIALsD82AtPIYXCWuaYq4\n\
ms5ISJnGi8ccVfMqNQDy385O8PaDYj2zc5Ofy0gTQwXDLNbF1/XYoX7hiiZn7sYF\n\
INHYF3nWx9FgubNSSTz1brgGhsXx+dI7OFE2K1m5wS7mbw1q9ipujLMN0kKuyWBV\n\
WiPTQNY4s5/UrqU7ofWbl/JqpVBjBOWyQM3mR0huVgwWUK3u+GSuRvAUOF9QbvaD\n\
EFo6I3dNCFXJC5UaIl5++HKNCorvP69cre5dZdYPg69IMfI62y8bgP3zo6Y+jS0k\n\
1Hxxcr8RosedLdVJeqQFbA3FOQK/sk+f9r57pogcQtm2+GkCAwEAAaMkMCIwCwYD\n\
VR0PBAQDAgQwMBMGA1UdJQQMMAoGCCsGAQUFBwMBMA0GCSqGSIb3DQEBBQUAA4IB\n\
AQBCxw17x2Vkt/1lt4hw2mAkQC13z3SAarZ4vEUR2koudSf7+tl2PegXji/bsScV\n\
k0SWvuz1lPdh3ASshHGSKzjeoiy8Y9Oh5NspAP2pnpYFJ7l2xlaIEkENuCL84XMK\n\
KRxNeLKvCAIIM2pcTcdeAhpdUIebCGZdvXOBFoxpr8lk4Re+OW1eCYhv6Y6pNTpJ\n\
mFM8QLQmHsoOe4Y/FC/uHgBmQVxZkGDeiLrWJq546hWW2OX06ubMTkOFWZNF6Nu7\n\
HAyGFm1yPTI79x78xYznv87ilxzVOA1oVyLt6qji79TqgCKSrkguZRlDObM4w07A\n\
T2VFC9NDfZKDQlQVTX+iSM8L\n\
-----END CERTIFICATE-----\n\0";


static LPCSTR s_TargetHost = "ZACHL-SBA1.redmond.corp.microsoft.com";

static BOOL DebuggerPort_SSL_GetCACert( UINT8** caCert, UINT32* certLen )
{
    *caCert   = (UINT8*)s_SelfSignedCert;
    *certLen = hal_strlen_s(s_SelfSignedCert);

    return TRUE;
}

static BOOL DebuggerPort_SSL_GetTargetHost( LPCSTR* strTargetHost )
{
    *strTargetHost = s_TargetHost;
    return TRUE;
}

static BOOL DebuggerPort_SSL_GetDeviceCert( UINT8** caCert, UINT32* certLen )
{
    *caCert   = (UINT8*)s_SelfSignedCert;
    *certLen = hal_strlen_s(s_SelfSignedCert);

    return TRUE;
}

IDebuggerPortSslConfig g_DebuggerPortSslConfig =
{
    DebuggerPort_SSL_GetCACert,
    DebuggerPort_SSL_GetTargetHost,
    DebuggerPort_SSL_GetDeviceCert,
};

