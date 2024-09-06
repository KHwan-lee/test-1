from flask import Flask, request, send_file, jsonify
import os
import random

app = Flask(__name__)

@app.route('/')
def hello():
    return 'hello world!'

# 클라이언트의 요청에 응답
@app.route('/start', methods=['POST'])
def greet_user():
    data = request.get_json()

    if 'user' in data:
        user_name = data['user']
        response_message = f"hello {user_name}"
    else:
        response_message = "No 'user' provided in the request."

    return {
        'response': response_message
    }

IMG_FOLDER = 'imgs'
app.config['IMG_FOLDER'] = IMG_FOLDER

def get_random_image_path():
    image_folder = app.config['IMG_FOLDER']
    image_files = [f for f in os.listdir(image_folder) if f.endswith(('.jpg', '.jpeg', '.png'))]

    if not image_files:
        return None

    random_image = random.choice(image_files)
    return os.path.join(image_folder, random_image)


# 이미지, 질문, 선택지 전송
@app.route('/get_items')
def get_question():
    random_image_path = get_random_image_path()

    if random_image_path:
        # 질문과 선택지 추가하여 JSON 응답 생성
        data_to_send = {
            'image_url': random_image_path,
            'question': 'Question1',
            'choices': ['Choice 1', 'Choice 2', 'Choice 3']
        }
        return jsonify(data_to_send)
    else:
        return 'No images available.'

# 랜덤 이미지 전송
@app.route('/random_image')
def send_random_image():
    random_image_path = get_random_image_path()
    if random_image_path:
        return send_file(random_image_path, mimetype='image/jpeg')
    else:
        return 'No images available.'

if __name__ == '__main__':
    app.run(host='0.0.0.0', port=5000, debug=True)