/*
 * DEBUG: section XXX
 */

#include "squid.h"
#include "HttpMsg.h"
#include "TextException.h"
#include "adaptation/Message.h"

Adaptation::Message::Message(): header(NULL)
{
}

Adaptation::Message::Message(Header *aHeader): header(NULL)
{
    set(aHeader);
}

Adaptation::Message::~Message()
{
    clear();
}

void
Adaptation::Message::clear()
{
    HTTPMSGUNLOCK(header);
    body_pipe = NULL;
}

void
Adaptation::Message::set(Header *aHeader)
{
    clear();
    if (aHeader) {
        header = HTTPMSGLOCK(aHeader);
        body_pipe = header->body_pipe;
    }
}

void
Adaptation::Message::copyTo(Message &dest)
{
	Must(!dest.body_pipe); // can relax if needed, but need !body_pipe->used()
    dest.clear();
    if (header) {
		if (header->body_pipe != NULL) {
			// check that it would not be too late to clone the pipe
			Must(!header->body_pipe->consumedSize());
			header->body_pipe->clearConsumer(); // if any
			// note: current header->body_pipe producer may later become
			// dest.body_pipe consumer and consume its own data
			// TODO: consumer should detect and short-circuit no-op adaptation
		}
		Header *copy = header->clone();
		dest.set(copy);
    }
}
