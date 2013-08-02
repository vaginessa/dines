
#include <dns_question.hpp>

#include <convert.hpp>

#include <iostream>
#include <arpa/inet.h>
#include <stdexcept>
#include <stdio.h>

using namespace std;

DnsQuestion::DnsQuestion(DnsQuestion& q)
{
    *this = q;
}

DnsQuestion& DnsQuestion::operator=(const DnsQuestion& q)
{
    _qdomain_str = q._qdomain_str;
    _qdomain_enc = q._qdomain_enc;
    _qtype = q._qtype;
    _qclass = q._qclass;

    // TODO
//    if (fuzzer.hasAddress((void*)&q.qtype)) {
//        fuzzer.delAddress((void*)&q.qtype);
//        fuzzer.addAddress((void*)&qtype, 2);
//    }

//    if (fuzzer.hasAddress((void*)&q.qclass)) {
//        fuzzer.delAddress((void*)&q.qclass);
//        fuzzer.addAddress((void*)&qclass, 2);
//    }

    return *this;
}

DnsQuestion::DnsQuestion(const string qdomain, const string qtype, const string qclass)
{
    unsigned myqtype;
    unsigned myqclass;

    if (qtype.at(0) == 'F') {
        throw runtime_error("NOT IMPLEMENTED");
        //fuzzer.addAddress(&this->qtype, 2);
        myqtype = 1;
    } else {
        myqtype = stringToQtype(qtype);
    }

    if (qclass.at(0) == 'F') {
        throw runtime_error("NOT IMPLEMENTED");
        //fuzzer.addAddress(&this->qclass, 2);
        myqclass = 1;
    } else {
        myqclass = stringToQclass(qclass);
    }

    *this = DnsQuestion(qdomain, myqtype, myqclass);
}

DnsQuestion::DnsQuestion(const string qdomain, unsigned qtype, unsigned qclass)
{
    // Domain
    _qdomain_str = qdomain;
    _qdomain_enc = domainEncode(qdomain);

    // qtype
    this->_qtype = qtype;

    // qclass
    this->_qclass = qclass;
}

string DnsQuestion::data() const
{
    string out = "";
    uint16_t temp;

    out += _qdomain_enc;

    temp = htons(_qtype);
    out += string((char*)&temp, 2);

    temp = htons(_qclass);
    out += string((char*)&temp, 2);

    return out;
}

string DnsQuestion::qdomain() const
{
    return _qdomain_str;
}

uint16_t DnsQuestion::qclass() const
{
    return _qclass;
}

uint16_t DnsQuestion::qtype() const
{
    return _qtype;
}
