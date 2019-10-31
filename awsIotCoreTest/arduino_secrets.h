// Fill in  your WiFi networks SSID and password
#define SECRET_SSID "GCAMP0724G"
#define SECRET_PASS "12345678a"

// Fill in the hostname of your AWS IoT broker
#define SECRET_BROKER "afmw36bze6igo-ats.iot.us-east-1.amazonaws.com"

// Fill in the boards public certificate
const char SECRET_CERTIFICATE[] = R"(
-----BEGIN CERTIFICATE-----
MIIC0DCCAbigAwIBAgIVAIbaWU9fqBFolieytIcoOoyBF7dFMA0GCSqGSIb3DQEB
CwUAME0xSzBJBgNVBAsMQkFtYXpvbiBXZWIgU2VydmljZXMgTz1BbWF6b24uY29t
IEluYy4gTD1TZWF0dGxlIFNUPVdhc2hpbmd0b24gQz1VUzAeFw0xOTEwMjQxNjA2
MzdaFw00OTEyMzEyMzU5NTlaMF8xCzAJBgNVBAYTAktSMQ4wDAYDVQQIEwVTZW91
bDEOMAwGA1UEBxMFU2VvdWwxDTALBgNVBAoTBHRlc3QxDTALBgNVBAsTBHRlc3Qx
EjAQBgNVBAMTCW5hbm8zM2lvdDBZMBMGByqGSM49AgEGCCqGSM49AwEHA0IABJIG
4X5t0G0UCMUOMUDzkD3zSSXCZhigbas7h0e0qvrNPCq3XyQ5eHIl0a7v3BuaWDec
srh4QnzV/4Sf1RFn+eOjYDBeMB8GA1UdIwQYMBaAFDvTVI2cK3bamSNTed+wtDdn
Z/kZMB0GA1UdDgQWBBREqOkwrdBl6maRwzFYjAmlpSphgTAMBgNVHRMBAf8EAjAA
MA4GA1UdDwEB/wQEAwIHgDANBgkqhkiG9w0BAQsFAAOCAQEAYUvdE9lFuOlUTYF+
KSLeCgXi9He9iNLVwZHwLpEE82j4Ace0WWKXfGr+UYRv5eA/fxJMUTy7c4Yutvik
Mj9VE+FLbMCKRw8YpcvPkN/rxiEEQh4mgKu6Uje6xUOPz+WHI/OGYLFVPdSMo6RP
mzKhHclx4cl0NKQD1iXjDzDFhQWn7CGDQ55f+Ql8ZpOdBoM5M4E50KdecoaA2poh
8MWTciW+r99vTWGb00L5I8jEHCKU6pFUd7b/dc7DpxwtsmnTKE4Tk9GCCcFS38nC
LYyTF/gs4UzWtKK5tw8zjBDmT+Z9Rjx2XgSUYgohP+e5Gou8jyYG3lMy9PDsVB+M
Cq9rXg==
-----END CERTIFICATE-----
)";
