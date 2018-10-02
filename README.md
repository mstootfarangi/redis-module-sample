# redis-module-sample
sample module on redis developed in C

## What it includes:

### 1. redismodule.h

The only file you really need to start writing Redis modules. Either put this path into your module's include path, or copy it.-

Notice: This is an up-to-date copy of it from the Redis repo.

### 2. An example Module

A minimal module implementing a few commands.

You can treat it as a template for your module, and extned its code and makefile.

**It includes 2 commands:**

* `GOOGOOLADD` - add new value to a list.
* `GOOGOOLCOUNT` - count number of emelents in a list.
