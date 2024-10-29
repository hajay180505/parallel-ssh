# Dockerfile
FROM alpine:latest

# Install OpenSSH
RUN apk update && apk add --no-cache openssh

# Generate SSH host keys
RUN ssh-keygen -A

# Configure SSH
RUN mkdir /var/run/sshd && \
    echo "PermitRootLogin yes" >> /etc/ssh/sshd_config && \
    echo "PasswordAuthentication yes" >> /etc/ssh/sshd_config

# Add two users and set passwords
RUN adduser -D user1 && echo "user1:password1" | chpasswd && \
    adduser -D user2 && echo "user2:password2" | chpasswd && \
    adduser -D user3 && echo "user3:password3" | chpasswd && \
    adduser -D user4 && echo "user4:password4" | chpasswd && \
    adduser -D user5 && echo "user5:password5" | chpasswd

# Expose SSH port
EXPOSE 22

# Start SSH daemon
CMD ["/usr/sbin/sshd", "-D"]
