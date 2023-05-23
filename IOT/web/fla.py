from flask import Flask

app = Flask(__name__)

@app.route('/')
def hello():
    return "hello"

@app.route('/page/<id>')
def page(id):
    return f"{id} Page OK"

if __name__=='__main__':
    app.run(debug=True, port=80, host='0.0.0.0')
