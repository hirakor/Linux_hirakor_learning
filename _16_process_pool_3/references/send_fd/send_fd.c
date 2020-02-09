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

int main(int argc,char *argv[])
{
    int fds[2];
    socketpair(AF_LOCAL,SOCK_STREAM,0,fds);
    if(!fork())
    {
        close(fds[1]);
        int childFd;
        recvFd(fds[0],&childFd);//接描述符
        char buf[128]={0};
        printf("I am child childFd=%d\n",childFd);
        read(childFd,buf,sizeof(buf));
        printf("I am child %s\n",buf);
    }else{
        close(fds[0]);
        int fd=open("file",O_RDWR);
        printf("I am parent fd=%d\n",fd);
        sendFd(fds[1],fd);
        wait(NULL);
    }
    return 0;
}

