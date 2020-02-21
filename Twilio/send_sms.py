from twilio.rest import Client

# NOTE THIS IS ONE OF MANY FILES USED FOR THE TWILIO PROJECT. THE IDEA WAS NOT INTENDED TO BE FULLY DISCLOSED TO THE PUBLIC


# Your Account Sid and Auth Token from twilio.com/console
account_sid = 'PNc6855f02322e32f832c291ba8731186d'
auth_token = '19e4f48fe8b1eebf00f91913c52f9e5f'
client = Client(account_sid, auth_token)

call = client.calls.create(
                     url="http://demo.twilio.com/docs/voice.xml",
                     from_='+16474961199',
                     to='+14168283752'
                 )

print(call.sid)
