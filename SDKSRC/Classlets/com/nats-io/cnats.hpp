// Copyright 2016 Ishbir Singh. All rights reserved.

#ifndef CNATS_HPP
#define CNATS_HPP

#include <nats.h>

natsConnection      *nc = NULL;
natsSubscription    *sub = NULL;
natsMsg             *msg = NULL;

// Connects to the default NATS Server running locally
natsConnection_ConnectTo(&nc, NATS_DEFAULT_URL);

// Connects to a server with username and password
natsConnection_ConnectTo(&nc, "nats://ivan:secret@localhost:4222");

// Connects to a server with token authentication
natsConnection_ConnectTo(&nc, "nats://myTopSecretAuthenticationToken@localhost:4222");

// Simple publisher, sending the given string to subject "foo"
natsConnection_PublishString(nc, "foo", "hello world");

// Publish binary data. Content is not interpreted as a string.
char data[] = { 1, 2, 0, 4, 5 };
natsConnection_Publish(nc, "foo", (const void*)data, 5);

// Simple asynchronous subscriber on subject foo, invoking message 
// handler 'onMsg' when messages are received, and not providing a closure.
natsConnection_Subscribe(&sub, nc, "foo", onMsg, NULL);

// Simple synchronous subscriber
natsConnection_SubscribeSync(&sub, nc, "foo");

// Using a synchronous subscriber, gets the first message available, waiting
// up to 1000 milliseconds (1 second)
natsSubscription_NextMsg(&msg, sub, 1000);

// Destroy any message received (asynchronously or synchronously) or created
// by your application. Note that if 'msg' is NULL, the call has no effect.
natsMsg_Destroy(msg);

// Unsubscribing
natsSubscription_Unsubscribe(sub);

// Destroying the subscription (this will release the object, which may
// result in freeing the memory). After this call, the object must no
// longer be used.
natsSubscription_Destroy(sub);

// Publish requests to the given reply subject:
natsConnection_PublishRequestString(nc, "foo", "bar", "help!");

// Sends a request (internally creates an inbox) and Auto-Unsubscribe the
// internal subscriber, which means that the subscriber is unsubscribed
// when receiving the first response from potentially many repliers.
// This call will wait for the reply for up to 1000 milliseconds (1 second).
natsConnection_RequestString(&reply, nc, "foo", "help", 1000);

// Closing a connection (but not releasing the connection object)
natsConnection_Close(nc);

// When done with the object, free the memory. Note that this call
// closes the connection first, in other words, you could have simply
// this call instead of natsConnection_Close() followed by the destroy
// call.
natsConnection_Destroy(nc);

// Message handler
void
onMsg(natsConnection *nc, natsSubscription *sub, natsMsg *msg, void *closure)
{
	// Prints the message, using the message getters:
	printf("Received msg: %s - %.*s\n",
		natsMsg_GetSubject(msg),
		natsMsg_GetDataLength(msg),
		natsMsg_GetData(msg));

	// Don't forget to destroy the message!
	natsMsg_Destroy(msg);
}



#endif