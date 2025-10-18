# =========================
# Stage 1: Build Liquibook
# =========================
FROM ubuntu:latest AS builder

# Install build dependencies
RUN apt-get update && apt-get install -y \
    build-essential \
    cmake \
    git \
    python3 \
    python3-pip \
    python3-build \
    python3-venv \
    swig \
    && rm -rf /var/lib/apt/lists/*

# Clone Liquibook repository
WORKDIR /app
RUN git clone -b pypi_setup https://github.com/mkipnis/liquibook liquibook

WORKDIR /app/liquibook

# Build and install Liquibook C++ core
RUN cmake -B build -S . -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=/usr/local \
    && cmake --build build --target install
RUN CMAKE_ARGS="-DLIQUIBOOK_SRC=$(pwd)/src -DBUILD_PYTHON=ON" python3 -m build --wheel

RUN python3 -m venv /opt/venv
ENV PATH="/opt/venv/bin:$PATH"

RUN pip install --upgrade pip setuptools wheel
RUN pip install dist/*.whl dash==3.0.4 dash-bootstrap-components==2.0.3 dash_ag_grid==31.3.1

EXPOSE 8050

COPY entrypoint.sh /usr/local/bin/entrypoint.sh
RUN chmod +x /usr/local/bin/entrypoint.sh
ENTRYPOINT ["/usr/local/bin/entrypoint.sh"]
