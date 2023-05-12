from flask import Flask

app = Flask(__name__)      
@app.route('/')
def index():
    return 'This is the index page'

@app.route('/user/<username>')
def show_user_profile(username):
    # show the user profile for that user
    return 'User is %s' % username

@app.route('/home')
def home():
    return 'Hi this is my home page'

if __name__ == '__main__':
	app.run(debug=True)