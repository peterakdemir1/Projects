import streamlit as st

st.markdown("# Where's My Alien?!")

tab1, tab2, tab3 = st.tabs(["Home", "Instructions", "Login"])

with tab1:
   st.header("Home")
   st.image("https://media.tenor.com/IIQ-ca9nBu0AAAAd/space.gif")
   description = '''Welcome to **Where's My Alien?!**

   Find a cheeky little alien in these user-uploaded images and get the best time!

   Upload your own images and send it to friends to see if they can find your alien!
   
   May the alien hunt begin!
   '''
   st.markdown(description)

with tab2:
   st.header("Instructions")
   st.image("https://static.streamlit.io/examples/dog.jpg", width=200)

with tab3:
   st.header("Login")
   st.image("https://static.streamlit.io/examples/owl.jpg", width=200)