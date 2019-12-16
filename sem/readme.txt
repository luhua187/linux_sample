1、sem_init 是posix信号量，进程退出会自动释放。常用线程操作；
2、semget 是兼容系统的v信号量（System V），必须明确对其进行删除操作；常用于进程间；
