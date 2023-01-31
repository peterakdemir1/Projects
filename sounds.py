import speech_recognition as sr
import soundfile as sf
import sounddevice as sd

# Initialize recognizer class (for recognizing the speech)
filename = 'sound.wav'
r = sr.Recognizer()

# Start recording audio
with sr.Microphone() as source:
    print("Talk\n")
    samplerate = 44100
    duration = 10
    audio = r.record(source=source, duration=duration)
    #audio = sd.rec(int(samplerate*duration), samplerate=samplerate, channels=2)
#    sd.wait()
#    sf.write(filename, audio, samplerate)

#print(type(audio))
#print(audio.shape)
# Perform speech recognition
try:
    print("You said: " + r.recognize_google(audio_data=audio, language='en-US'))
except Exception as e:
    print("Error: " + str(e))
