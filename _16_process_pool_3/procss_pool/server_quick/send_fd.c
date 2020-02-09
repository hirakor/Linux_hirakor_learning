#include <func.h>

int sendFd(int sfd,int fd)
{
    struct msghdr msg;
    bzero(&msg,sizeof(msg));
    //用户态要给对方什么信息
    struct iovec iov[1];
    char buf[10]="hello";
    iov[0].iov_base=buf;
    iov[0].iov_len=5;
    msg.msg_iov=iov;
    msg.msg_iovlen=1;
    //内核控制信息要传递那个
    struct cmsghdr *cmsg;
    int len=CMSG_LEN(sizeof(int));
    cmsg=(struct cmsghdr *)calloc(1,len);
    cmsg->cmsg_len=len;
    cmsg->cmsg_level=SOL_SOCKET;
    cmsg->cmsg_type = SCM_RIGHTS;
    *(int*)CMSG_DATA(cmsg)=fd;
    msg.msg_control=cmsg;
    msg.msg_controllen=len;
    int ret;
    ret=sendmsg(sfd,&msg,0);
    ERROR_CHECK(ret,-1,"sendmsg");
    return 0;
}
int recvFd(int sfd,int *fd)
{
    struct msghdr msg;
    bzero(&msg,sizeof(msg));
    //用户态要接什么信息
    struct iovec iov[1];
    char buf[10]={0};
    iov[0].iov_base=buf;
    iov[0].iov_len=5;
    msg.msg_iov=iov;
    msg.msg_iovlen=1;
    //内核控制信息要传递那个
    struct cmsghdr *cmsg;
    int len=CMSG_LEN(sizeof(int));
    cmsg=(struct cmsghdr *)calloc(1,len);
    cmsg->cmsg_len=len;
    cmsg->cmsg_level=SOL_SOCKET;
    cmsg->cmsg_type = SCM_RIGHTS;
    msg.msg_control=cmsg;
    msg.msg_controllen=len;
    int ret;
    ret=recvmsg(sfd,&msg,0);
    ERROR_CHECK(ret,-1,"recvmsg");
    *fd=*(int*)CMSG_DATA(cmsg);//拿到控制信息在当前进程中的位置
    return 0;
}

