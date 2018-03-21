

# Build
```
npm run build
```

# Watch

```
npm run watch
```


# Editor
If you use `vscode`, Press `Windows + Shift + B` it will build automatically

# Google container registry

* eval $(minikube docker-env)
* docker build -t onetimeurl-198513/app:v1 .
* docker tag onetimeurl-198513/app:v1 gcr.io/onetimeurl-198513/app:v1
* gcloud docker -- push gcr.io/onetimeurl-198513/app:v1
* kubectl run app --image=gcr.io/onetimeurl-198513/app:v1 --port 3000
* kubectl delete deployment app
* kubectl expose deployment app --type=LoadBalancer
* minikube service app
* kubectl set image deployment/app app=app:v2

## Kompose

* kompose convert -f docker-compose.yml

## Local registry

* docker tag onetimeurl/app:v1 localhost:5000/onetimeurl/app:v1
* docker push localhost:5000/onetimeurl/app:v1

# Kubernetess

* minikube start --vm-driver=kvm2
* minikube dashboard
* kubectl cluster-info [dump]
* kubectl get nodes
* kubectl (get|describe|logs|exec)
* export POD_NAME=$(kubectl get pods -o go-template --template '{{range .items}}{{.metadata.name}}{{"\n"}}{{end}}')
* kubectl --namespace=$NAMESPACE create secret docker-registry gcr \
          --docker-server=https://gcr.io \
          --docker-username=oauth2accesstoken \
          --docker-password="$(gcloud auth print-access-token)" \
          --docker-email="$(gcloud auth list --filter=status:ACTIVE --format='value(account)')"
* $ kubectl --namespace=$NAMESPACE patch serviceaccount default \
    -p '{"imagePullSecrets": [{"name": "gcr"}]}'
* kubectl --namespace=$NAMESPACE delete secret gcr
