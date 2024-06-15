@echo off
SETLOCAL
set PASS=123456987

set OPENSSL_CONF=C:\msys64\usr\ssl\openssl.cnf
REM ����֤���ļ���
set "CA_CERT=ca.crt"
set "CA_KEY=ca.key"
set "CA_SUBJECT=/C=US/ST=State/L=City/O=Organization/OU=Unit/CN=RootCA"

set "LOCK_KEY=lock.key"
set "LOCK_CSR=lock.csr"
set "LOCK_CERT=lock.crt"
set "LOCK_SUBJECT=/C=US/ST=State/L=City/O=Organization/OU=Unit/CN=192.168.101.9"

REM ���ca.crt�Ƿ����
if not exist "%CA_CERT%" (
    echo ca.crt �����ڣ������µ� CA ֤�����Կ...
    REM ���� CA ˽Կ
    openssl req -newkey rsa:2048 -x509 -new -nodes -sha256 -days 3650 -keyout "%CA_KEY%" -out "%CA_CERT%" -subj "%CA_SUBJECT%" -passout pass:%PASS%
) else (
    echo ca.crt �Ѵ��ڣ����� CA ֤������...
)

REM ɾ�����е� lock.key, lock.csr, lock.crt
echo ɾ�����е� %LOCK_KEY%, %LOCK_CSR%, %LOCK_CERT%...
del /f "%LOCK_KEY%" "%LOCK_CSR%" "%LOCK_CERT%" 2>nul


REM ���� CSR
echo �����µ�֤��ǩ������CSR��...
openssl req -new -newkey rsa:2048 -keyout "%LOCK_KEY%" -out "%LOCK_CSR%" -subj "%LOCK_SUBJECT%"  -passout pass:%PASS%

REM ʹ�� CA ǩ�� CSR�����ɷ�����֤��
echo ʹ�� CA ǩ�� CSR�����ɷ�����֤��...
openssl x509 -req -in "%LOCK_CSR%" -CA "%CA_CERT%" -CAkey "%CA_KEY%" -CAcreateserial -out "%LOCK_CERT%" -days 365 -sha256 -passin pass:%PASS%

echo ������ɡ����ɵ��ļ��У�
echo   CA ֤��: %CA_CERT%
echo   CA ˽Կ: %CA_KEY%
echo   ������˽Կ: %LOCK_KEY%
echo   ������֤��: %LOCK_CERT%
endlocal
pause