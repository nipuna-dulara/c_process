#!/bin/bash
echo '#!/bin/bash' > /tmp/test1.sh
echo 'echo "Test 1 executed"' >> /tmp/test1.sh
chmod +x /tmp/test1.sh

echo '#!/bin/bash' > /tmp/test2.sh
echo 'echo "Test 2 executed"' >> /tmp/test2.sh
chmod +x /tmp/test2.sh

echo '#!/bin/bash' > /tmp/test3.sh
echo 'echo "Test 3 executed"' >> /tmp/test3.sh
chmod +x /tmp/test3.sh

gcc -o lab1p1 lab1p1.c

echo "Testing 1:"
./lab1p1 "/bin/echo Hello + /bin/echo World + /tmp/test1.sh + /tmp/test2.sh + /tmp/test3.sh"

echo "Testing 2:"
./lab1p1 "/bin/echo Linux is cool + /bin/echo But I am sleepy + /bin/echo Going to sleep now + /bin/sleep 5 + /bin/echo Now I am awake"
rm /tmp/test1.sh /tmp/test2.sh /tmp/test3.sh lab1p1
