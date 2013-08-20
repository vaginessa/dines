Dines
=====

[![Build Status](https://travis-ci.org/crondaemon/dines.png)](https://travis-ci.org/crondaemon/dines)

Dines is the definitive answer to DNS testing. It allows the creation of any DNS packet with the possibility to fuzz some fields. Used in shell scripts allows also the creation of fake DNS servers that answer in custom ways.

Compilation
-----------
To compile dines:

    autoreconf -i
    ./configure
    make

To run dines tests:

    make tests

Usage
-----

This is the help from dines.


    Dines 0.4 - The definitive DNS packet forger.

    Fields with (F) can be fuzzed. (Example --txid F)
    Fields with (R) are repeatable. (Example --answer)
    Fields with (A) are calculated automatically.

    Usage: ./dines <params>

    Params:

    [IP]
    --src-ip <ip>: Source IP (AF)
    --dst-ip <ip>: Destination IP

    [UDP]
    --sport <port>: source port (A)
    --dport <port>: destination port (A)

    [DNS]
    --txid <id>: transaction id (AF)
    --num-questions <n>: number of questions (AF)
    --question <domain>,<type(F)>,<class(F)>: question domain

    --num-ans <n>: number of answers (AF)
    --answer(R) <domain>,<type(F)>,<class(F)>,<ttl(F)>,<rdata>: a DNS answer
    --answer(R) <domain>,<type(F)>,<class(F)>,<ttl(F)>,<rdatalen>,<rdata>: a DNS answer

    --num-auth <n>: number of authoritative records (AF)
    --auth(R) <domain>,<type>,<class(F)>,<ttl(F)>,<rdata>: a DNS authoritative record
    --auth(R) <domain>,<type>,<class(F)>,<ttl(F)>,<rdatalen>,<rdata>: a DNS authoritative record

    --num-add <n>: number of additional records (AF)
    --additional(R) <domain>,<type(F)>,<class(F)>,<ttl(F)>,<rdata>: a DNS additional record
    --additional(R) <domain>,<type(F)>,<class(F)>,<ttl(F)>,<rdatalen>,<rdata>: a DNS additional record

    [MISC]
    --server <port>: run in server mode on port (A)
    --num <n>: number of packets (0 = infinite)
    --delay <usec>: delay between packets
    --verbose: be verbose
    --help: this help

To generate a question, issue the follogin command:

    sudo ./dines --src-ip 192.168.1.1 --dst-ip 192.168.1.2 --question www.test.com,A,IN --num 1

that asks for domain www.test.com, sending 1 packet only. To generate an answer, one can use the following
command

    sudo ./dines --src-ip 192.168.1.1 --dst-ip 192.168.1.2 --question www.test.com,1,1 --num 1
        --answer www.test.com,1,1,256,192.168.1.1 --answer www.test.com,1,1,256,192.168.1.2

The switches related to resource records can be repeated multiple times. When resource record switches are used
in short mode (without rdatalen), rdata is converted according to the query type. Qtype A is converted
as an IP address, NS as a DNS name, and so on. To inject binary data directly, the extended mode can be used,
as in the following example

    sudo ./dines --src-ip 192.168.1.1 --dst-ip 192.168.1.2 --question www.test.com,NULL,IN --num 1
        --answer www.test.com,NULL,IN,0,10,$'\x01\x02\x03\x04\x05\x06\x07\x08\x09\x0a'

Server Mode
-----------
Since version 0.5, dines supports server mode, that implements a minimalistic DNS server that serves arbitrary
data. The syntax is the very same as in client mode: to activate server mode the user must specify --server
with the UDP port the server listens on.
