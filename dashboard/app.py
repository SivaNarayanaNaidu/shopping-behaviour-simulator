import streamlit as st
import pandas as pd
import plotly.express as px

st.set_page_config(page_title="AI Shopping Behaviour Simulator", layout="wide")

st.title("🛍️ AI Shopping Behaviour Simulator Dashboard")
st.markdown("Analyze the purchasing patterns of simulated AI customer agents.")

@st.cache_data
def load_data():
    try:
        events_df = pd.read_csv("events.csv")
        products_df = pd.read_csv("products.csv")
        return events_df, products_df
    except FileNotFoundError:
        return None, None

events_df, products_df = load_data()

if events_df is None or products_df is None:
    st.warning("Data files (events.csv, products.csv) not found. Please run the simulator first.")
else:
    # --- KPIs ---
    st.header("Key Metrics")
    col1, col2, col3, col4 = st.columns(4)
    
    total_revenue = events_df[events_df['event_type'] == 'Purchase']['value'].sum()
    total_sessions = events_df['agent_id'].nunique() # Approx based on unique agents with events
    total_purchases = len(events_df[events_df['event_type'] == 'Purchase'])
    cart_adds = len(events_df[events_df['event_type'] == 'CartAddition'])
    cart_abandons = len(events_df[events_df['event_type'] == 'CartAbandonment'])
    
    conversion_rate = (total_purchases / total_sessions) * 100 if total_sessions > 0 else 0
    abandon_rate = (cart_abandons / (cart_adds + 1e-5)) * 100 # Approx carts abandoned vs items added
    
    col1.metric("Total Revenue", f"${total_revenue:,.2f}")
    col2.metric("Total Purchases", total_purchases)
    col3.metric("Conversion Rate", f"{conversion_rate:.1f}%")
    col4.metric("Active Shoppers", total_sessions)

    # --- Charts ---
    st.header("Behavioral Analysis")
    col_chart1, col_chart2 = st.columns(2)

    with col_chart1:
        st.subheader("Event Funnel")
        funnel_data = events_df['event_type'].value_counts().reset_index()
        funnel_data.columns = ['Event', 'Count']
        # Order the funnel
        order = ['ProductView', 'CartAddition', 'CartAbandonment', 'Purchase']
        funnel_data['Event'] = pd.Categorical(funnel_data['Event'], categories=order, ordered=True)
        funnel_data = funnel_data.sort_values('Event')
        
        fig = px.funnel(funnel_data, x='Count', y='Event', title="Shopping Funnel")
        st.plotly_chart(fig, use_container_width=True)

    with col_chart2:
        st.subheader("Revenue by Agent Type")
        purchases = events_df[events_df['event_type'] == 'Purchase']
        rev_by_type = purchases.groupby('agent_type')['value'].sum().reset_index()
        fig2 = px.pie(rev_by_type, values='value', names='agent_type', title="Revenue Contribution by Customer Profile")
        st.plotly_chart(fig2, use_container_width=True)
        
    st.header("Daily Trends")
    st.subheader("Simulated Daily Revenue")
    daily_rev = purchases.groupby('day')['value'].sum().reset_index()
    fig3 = px.line(daily_rev, x='day', y='value', title="Revenue over Simulation Period (30 Days)", markers=True)
    st.plotly_chart(fig3, use_container_width=True)
