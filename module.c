#include "redismodule.h"

/*
 * GOOGOOLAdd <list_name> <value>
 * Add a value to a list
 */
int GOOGOOLAddCommand(RedisModuleCtx *ctx, RedisModuleString **argv, int argc) {

    // we need EXACTLY 3 arguments
    if (argc != 3) {
        return RedisModule_WrongArity(ctx);
    }
    RedisModule_AutoMemory(ctx);

    // add new element to list
    RedisModuleCallReply *rep =
        RedisModule_Call(ctx, "RPUSH", "ss", argv[1], argv[2]);
    REDISMODULE_NOT_USED(argv);
    RedisModule_ReplyWithCallReply(ctx,rep);
    return REDISMODULE_OK;
}


/*
 * GOOGOOLCount <list_name>
 * Count number of items in a list
 */
int GOOGOOLCountCommand(RedisModuleCtx *ctx, RedisModuleString **argv, int argc)
{
    if (argc != 2) {
        return RedisModule_WrongArity(ctx);
    }

    RedisModuleCallReply *rep = 
        RedisModule_Call(ctx,"LRANGE","sll",argv[1],(long long)0,(long long)-1);
    size_t count = RedisModule_CallReplyLength(rep);
    RedisModule_ReplyWithLongLong(ctx,count);
    return REDISMODULE_OK;
}

int RedisModule_OnLoad(RedisModuleCtx *ctx) {

    // Register the module itself
    if (RedisModule_Init(ctx, "list", 1, REDISMODULE_APIVER_1) ==
            REDISMODULE_ERR) {
        return REDISMODULE_ERR;
    }

    // register googooladd - using the shortened utility registration macro
    if (RedisModule_CreateCommand(ctx,"googooladd",
                GOOGOOLAddCommand,"write",1,1,1) == REDISMODULE_ERR)
        return REDISMODULE_ERR;
    // register googoolcount - using the shortened utility registration macro
    if (RedisModule_CreateCommand(ctx,"googoolcount",
                GOOGOOLCountCommand,"write",1,1,1) == REDISMODULE_ERR)
        return REDISMODULE_ERR;

    return REDISMODULE_OK;
}
