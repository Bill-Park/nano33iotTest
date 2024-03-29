// Fill in  your WiFi networks SSID and password
#define SECRET_SSID ""
#define SECRET_PASS ""

// Fill in the hostname of your AWS IoT broker
#define SECRET_BROKER "afmw36bze6igo-ats.iot.us-east-1.amazonaws.com"

// Fill in the boards public certificate
const char SECRET_CERTIFICATE[] = R"(
-----BEGIN CERTIFICATE-----
MIICqzCCAZOgAwIBAgIVANDuy7NyV/zSxfI6SK3cb3bxTxsFMA0GCSqGSIb3DQEB
CwUAME0xSzBJBgNVBAsMQkFtYXpvbiBXZWIgU2VydmljZXMgTz1BbWF6b24uY29t
IEluYy4gTD1TZWF0dGxlIFNUPVdhc2hpbmd0b24gQz1VUzAeFw0xOTExMDIwOTQz
MDhaFw00OTEyMzEyMzU5NTlaMDoxCzAJBgNVBAYTAktSMQ4wDAYDVQQIEwVTZW91
bDEbMBkGA1UEAxMSMDEyMzRBQzkxM0U0RjVBOUVFMFkwEwYHKoZIzj0CAQYIKoZI
zj0DAQcDQgAEV2eZ2AM98jPfuCuxQMgN1dHUttYfOkaqCXPaZZtE5s6y1RZDPktO
DfHLFvm+0SNqFecDq7Drg/I5fHWeublBSqNgMF4wHwYDVR0jBBgwFoAU2a3ER55D
rWV/Gu1sP1lGo14z5HQwHQYDVR0OBBYEFAXDjJf1Nb84JMhn0bU4k4KTMaxwMAwG
A1UdEwEB/wQCMAAwDgYDVR0PAQH/BAQDAgeAMA0GCSqGSIb3DQEBCwUAA4IBAQCn
lZ2vqGt96ljCK41+cO8GDyMyGe+A5YXiTpJU/Obd5DXfsFRQMz5ts9LTE+qF41Gc
pc1TAVIlCONiwN4IzgLN7bBiQR0/AzQsUfPBHFzTRUcXcXX4ANxtgUXGlhOB12gU
7DlTQHmZFBWqPQSZUkuPyo7F1ODi2v8esUNdxnk/uHM/fUpRkZWLkJGMZg3wR2Qf
ZFeXiuC2r9Tidj5FUSrEpufPBOzBgRDjkbkaR2Xv4dofo3W+lyeKxaofUEEKuEJ1
5MeVjRdgUsLXYJWQ4vqtqaA1kMkZZdqxe/sFi6RVrGir2h3JtlB8OMzVdRT1Hg/z
w+5HRlWnMa+0UGgDh9xg
-----END CERTIFICATE-----
)";
