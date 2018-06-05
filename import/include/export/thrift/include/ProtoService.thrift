namespace cpp proto_rpc
struct ProtoRequest{
	1: required i32 type;
	2: required i64 sharding_id;
	3: required string content;
}

struct ProtoReply{
	1: required i32 type;
	2: required i64 result;
	3: required string content;
}

service ProtoRpcService{
	ProtoReply dealTwowayMessage(1: ProtoRequest rq)
	void dealOnewayMessage(1: ProtoRequest rq) 
}
