from firebase import firebase
import time


# the generated root for your project
FIREBASE_ROOT = 'https://sound-guided-car.firebaseio.com'
# init Firebase Database instance
firebase = firebase.FirebaseApplication(FIREBASE_ROOT, None)


while True:
    # execute a GET request on the node
    result = firebase.get('/location', None)
    # log the result
    print result
    # wait 1 second between two consecutive requests
    time.sleep(3)
    #if result == "Up"
    result = firebase.put('location','position','Down')
    #else
    time.sleep(3)
    result = firebase.put('location','position','Up')
    print result
    time.sleep(3)